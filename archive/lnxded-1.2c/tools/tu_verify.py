#!/usr/bin/env python3
"""Verify one reconstructed translation unit against the original, with a real link.

usage: tu_verify.py OBJ TEXT_VA [-v]

The object's .text is placed at TEXT_VA. Every other address -- the object's own
.rodata/.data/.bss bases and each undefined symbol -- is solved from the original
bytes at the relocation sites (base = dword - addend) and must agree at every
site. The object is then linked by ld with exactly those addresses, and each
output section is compared byte-for-byte with the original at the same address.
A solved address is a layout claim only; the section contents must still match.
"""
import os, re, struct, subprocess, sys, tempfile

# The original is the binary named in the target's checksums.yml, in binaries/linux/.
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAME = next(l[:-1] for l in open(os.path.join(ROOT, 'checksums.yml')).read().splitlines() if l.endswith(':') and not l[0] in ' #')
ORIG = os.environ.get('ANCHOR', os.path.join(ROOT, '../../binaries/linux', NAME))

def elf(path):
    b = open(path, 'rb').read()
    shoff, = struct.unpack_from('<I', b, 0x20); shnum, shstr = struct.unpack_from('<HH', b, 0x30)
    sh = [struct.unpack_from('<10I', b, shoff + i * 40) for i in range(shnum)]
    so = sh[shstr][4]
    nm = lambda o, base: b[base + o:b.index(b'\0', base + o)].decode()
    secs = [(nm(s[0], so), s) for s in sh]
    syms = []
    for i, (n, s) in enumerate(secs):
        if s[1] == 2:
            strb = sh[s[6]][4]
            for k in range(s[5] // 16):
                st_name, val, size, info, oth, shndx = struct.unpack_from('<IIIBBH', b, s[4] + k * 16)
                syms.append((nm(st_name, strb), val, size, info, shndx))
    rels = {}
    for n, s in secs:
        if s[1] == 9:
            tgt = secs[s[7]][0]
            rels[tgt] = [struct.unpack_from('<II', b, s[4] + k * 8) for k in range(s[5] // 8)]
    return b, secs, syms, rels

# section headers of the original: (va, file offset, size)
_, _osecs, _, _ = elf(ORIG)
_osh = {n: (s[3], s[4] if s[1] != 8 else None, s[5]) for n, s in _osecs}
OSEC = {n: _osh[n] for n in ('.text', '.rodata', '.data', '.gcc_except_table', '.bss')}
EH = _osh['.eh_frame']
CRTSEC = {n: _osh[n] for n in ('.ctors', '.dtors', '.jcr')}   # the crt's list sections
GOT = _osh.get('.got.plt', _osh['.got'])[0]
PLT = _osh['.plt'][0]

def fdes(b):
    """pc_begin -> FDE bytes with the CIE pointer blanked (it depends on CIE merging)."""
    out, i = {}, 0
    while i + 8 <= len(b):
        ln, cid = struct.unpack_from('<II', b, i)
        if ln == 0: break
        if cid:
            pc, = struct.unpack_from('<I', b, i + 8)
            out[pc] = b[i:i + 4] + b'\0' * 4 + b[i + 8:i + 4 + ln]
        i += 4 + ln
    return out

def main():
    obj = sys.argv[1]
    text_va = 0 if sys.argv[2] == '-' else int(sys.argv[2], 16)     # '-': a TU with no code
    verbose = '-v' in sys.argv
    orig = open(ORIG, 'rb').read()
    b, secs, syms, rels = elf(obj)
    sec_of = {i: n for i, (n, s) in enumerate(secs)}
    solved, conflicts = {}, []
    for off, info in rels.get('.text', []):
        typ, si = info & 0xff, info >> 8
        name, val, size, sinfo, shndx = syms[si]
        A, = struct.unpack_from('<i', b, secs[[n for n, _ in secs].index('.text')][1][4] + off)
        site = text_va + off
        d, = struct.unpack_from('<I', orig, OSEC['.text'][1] + site - OSEC['.text'][0])
        tgt = (d + site) & 0xffffffff if typ == 2 else d          # PC32 addend already includes -4
        stype = sinfo & 0xf
        if stype == 3:                                           # section symbol: solve its base
            key = sec_of[shndx]; base = (tgt - A) & 0xffffffff
        elif shndx in (0, 0xfff2):                               # undefined or COMMON (placed by the final link): solve the symbol
            key = name; base = (tgt - A) & 0xffffffff
        elif sec_of[shndx] != '.text':                           # defined data: solves its section base
            key = sec_of[shndx]; base = (tgt - A - val) & 0xffffffff
        else:
            continue                                            # defined in this .text: ld resolves it
        if key in solved and solved[key] != base: conflicts.append((key, hex(solved[key]), hex(base), hex(off)))
        solved.setdefault(key, base)
    # Externals referenced only from data (function tables): solve from the placed section's slot.
    for sn in ('.data', '.rodata'):
        if sn not in solved or sn not in OSEC: continue
        sb = secs[[n for n, _ in secs].index(sn)][1]
        for off, info in rels.get(sn, []):
            name, val, size, sinfo, shndx = syms[info >> 8]
            if (info & 0xff) != 1 or shndx not in (0, 0xfff2) or name in solved: continue
            A, = struct.unpack_from('<i', b, sb[4] + off)
            lo, fo, sz = OSEC[sn]
            if not lo <= solved[sn] + off < lo + sz: continue
            d, = struct.unpack_from('<I', orig, fo + solved[sn] + off - lo)
            solved[name] = (d - A) & 0xffffffff
    # Imported libc names are real (the dynamic symbol table keeps them): each must
    # bind to its own PLT slot or copy-relocated object, and no other name may.
    # binutils 2.16 leaves an import's .dynsym value 0: its PLT slot follows from its .rel.plt index.
    dyn, slot = {}, 0
    for l in subprocess.run(['readelf', '-rW', ORIG], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'^[0-9a-f]{8}\s+[0-9a-f]+\s+R_386_(JUMP_SLOT|COPY)\s+([0-9a-f]+)\s+(\w+)', l)
        if not m: continue
        if m.group(1) == 'JUMP_SLOT':
            slot += 1; dyn[m.group(3)] = PLT + 16 * slot
        else: dyn[m.group(3)] = int(m.group(2), 16)
    byaddr = {v: k for k, v in dyn.items()}
    # Imports no .text site reaches (e.g. called only from a link-once inline).
    for name, val, size, sinfo, shndx in syms:
        if shndx == 0 and name in dyn and name not in solved: solved[name] = dyn[name]
    for k, v in solved.items():
        if k.startswith('.'): continue
        if k in dyn and dyn[k] != v: conflicts.append((k, 'is libc %#x' % dyn[k], 'but sites want %#x' % v, byaddr.get(v, '')))
        elif k not in dyn and v and v in byaddr: conflicts.append((k, 'binds to libc', byaddr[v], hex(v)))
    # One address per global name across every TU, as the final link will demand.
    # Defined names are claimed at their solved VA after the link below.
    import glob, json
    ledger = {}
    me = os.path.abspath(obj)
    for f in glob.glob(os.path.join(os.path.dirname(me), '*.syms.json')):
        if f != me[:-2] + '.syms.json':
            for k, v in json.load(open(f)).items(): ledger.setdefault(k, (v, os.path.basename(f)[:-10]))
    # Data no .text site here reaches: a verified TU that references it fixes the section base.
    for name, val, size, sinfo, shndx in syms:
        sn = sec_of.get(shndx)
        if sn and sn != '.text' and not sn.startswith('.lo.') and sn not in solved and (sinfo >> 4) == 1 and name in ledger:
            solved[sn] = ledger[name][0] - val
    # Still unplaced .data (only data refers to it): its relocated contents must occur exactly once.
    for sn, sh in secs:
        if sn != '.data' or sn in solved or sn not in OSEC or not sh[5]: continue
        have, mask = bytearray(b[sh[4]:sh[4] + sh[5]]), bytearray(b'\xff' * sh[5])
        for off, info in rels.get(sn, []):
            name, val, size, sinfo, shndx = syms[info >> 8]
            A, = struct.unpack_from('<i', b, sh[4] + off)
            key = sec_of.get(shndx) if sinfo & 0xf == 3 else name if shndx in (0, 0xfff2) else None
            if (info & 0xff) == 1 and key in solved: struct.pack_into('<I', have, off, (solved[key] + A) & 0xffffffff)
            else: mask[off:off + 4] = bytes(4)
        if sum(1 for m in mask if m) < 16: continue
        lo, fo, sz = OSEC[sn]
        hits = [a for a in range(0, sz - sh[5] + 1, max(sh[8], 1))
                if all(orig[fo + a + i] == have[i] for i in range(min(64, sh[5])) if mask[i])
                and all(orig[fo + a + i] == have[i] for i in range(sh[5]) if mask[i])]
        if len(hits) == 1: solved[sn] = lo + hits[0]
    # A section reached only through a placed data slot (a pointer to own storage): solve its base there.
    for sn in ('.data', '.rodata'):
        if sn not in solved or sn not in OSEC: continue
        sb = secs[[n for n, _ in secs].index(sn)][1]
        for off, info in rels.get(sn, []):
            name, val, size, sinfo, shndx = syms[info >> 8]
            key = sec_of.get(shndx)
            if (info & 0xff) != 1 or sinfo & 0xf != 3 or key in solved or key not in OSEC: continue
            A, = struct.unpack_from('<i', b, sb[4] + off)
            lo, fo, sz = OSEC[sn]
            if not lo <= solved[sn] + off < lo + sz - 3: continue          # a mis-solved base (changed code)
            d, = struct.unpack_from('<I', orig, fo + solved[sn] + off - lo)
            solved[key] = (d - A) & 0xffffffff
    for k, v in solved.items():
        if not k.startswith('.') and k in ledger and ledger[k][0] != v:
            conflicts.append((k, '%#x here' % v, '%#x in %s' % ledger[k]))
    if conflicts:
        print('address conflicts (the object disagrees with the original layout):')
        for c in conflicts[:20]: print('  ', *c)
    # Link-once header inlines (.lo.*): a copy the calls here resolve is placed there;
    # an unresolved one is this TU's own only if the original has it right after .text.
    end = text_va + secs[[n for n, _ in secs].index('.text')][1][5]
    own = set()
    for n, sh in secs:
        if not n.startswith('.lo.'): continue
        at = (end + sh[8] - 1) & -sh[8]
        if n not in solved:
            lo, fo, sz = OSEC['.text']
            want, have = bytearray(orig[fo + at - lo:fo + at - lo + sh[5]]), bytearray(b[sh[4]:sh[4] + sh[5]])
            for off, _ in rels.get(n, []):                       # relocated operands are resolved by the link
                want[off:off + 4] = have[off:off + 4] = bytes(4)
            if want != have: continue
            solved[n] = at
        if solved[n] == at: end = at + sh[5]; own.add(n)
    # Externals (and other TUs' link-once copies) called only from an owned inline copy: solve from its sites.
    # Repeat from every copy placed in this TU, so a chain of inline calls resolves.
    done = set()
    while True:
        todo = [n for n, sh in secs if n.startswith('.lo.') and n not in done and n in solved
                and text_va <= solved[n] < OSEC['.text'][0] + OSEC['.text'][2]]
        if not todo: break
        for n in todo:
            done.add(n)
            sh = dict(secs)[n]
            for off, info in rels.get(n, []):
                    name, val, size, sinfo, shndx = syms[info >> 8]
                    lo = sec_of.get(shndx, '')
                    key = lo if lo.startswith('.lo.') else name          # or a copy only this inline calls
                    if (shndx != 0 and key == name) or key in solved: continue
                    A, = struct.unpack_from('<i', b, sh[4] + off)
                    site = solved[n] + off
                    d, = struct.unpack_from('<I', orig, OSEC['.text'][1] + site - OSEC['.text'][0])
                    solved[key] = ((d + site if (info & 0xff) == 2 else d) - A - (val if key == lo else 0)) & 0xffffffff
    # Copies owned by an earlier TU that no .text site pins: park them out of the way.
    # addresses solved from changed code can land outside the image; ld chokes on them
    bad = lambda k, v: not 0x08040000 <= v < 0x0a000000 or (k in OSEC and not OSEC[k][0] <= v <= OSEC[k][0] + OSEC[k][2])
    for k in [k for k, v in solved.items() if v and bad(k, v)]:
        conflicts.append((k, 'solved outside the image', hex(solved.pop(k))))
    park = 0x01000000
    for n, sh in secs:
        if n.startswith('.lo.') and n not in solved:
            solved[n] = park; park += (sh[5] + 15) & -16
    with tempfile.TemporaryDirectory() as td:
        out = os.path.join(td, 'o.elf')
        cmd = ['ld', '-m', 'elf_i386', '-e', '0', '--no-warn-rwx-segments', '--unresolved-symbols=ignore-all', '--no-check-sections', '-Ttext=%#x' % text_va, '-o', out]
        for k, v in solved.items():
            if k.startswith('.'):
                if k != '.text': cmd.append('--section-start=%s=%#x' % (k, v))
            else: cmd.append('--defsym=%s=%#x' % (k, v))
        # crtbegin/crtend list pieces: an empty one opens its section (ELF header),
        # a non-empty one sits where its contents occur once in the original section.
        for n, sh in secs:
            if n not in CRTSEC or n in solved: continue
            lo, fo, sz = CRTSEC[n]
            have = b[sh[4]:sh[4] + sh[5]]
            hits = [a for a in range(0, sz - len(have) + 1, 4) if orig[fo + a:fo + a + len(have)] == have] if have else [0]
            if len(hits) == 1:                                  # the host ld files these as init/fini arrays
                out_n = {'.ctors': '.init_array', '.dtors': '.fini_array'}.get(n, n)
                cmd += ['--section-start=%s=%#x' % (m, lo + hits[0]) for m in {n, out_n}]
        if '.eh_frame' in dict(secs) and not dict(secs)['.eh_frame'][5]:   # crtbegin's __EH_FRAME_BEGIN__
            cmd = [c for c in cmd if not c.startswith('--section-start=.eh_frame=')]
            cmd.append('--section-start=.eh_frame=%#x' % EH[0])
            # ld drops an empty output section and files a writable one with .data:
            # link a read-only copy plus a trailing word
            ro = os.path.join(td, 'ro.o')
            subprocess.run(['objcopy', '--set-section-flags', '.eh_frame=alloc,load,readonly,data', obj, ro], check=True)
            pad = os.path.join(td, 'pad.o')
            subprocess.run(['as', '--32', '-o', pad], input='.section .eh_frame,"a"\n.long 0\n', text=True, check=True)
        cmd += ['--section-start=.got.plt=%#x' % GOT, '--section-start=.got=%#x' % GOT]
        if os.path.exists(os.path.join(td, 'pad.o')): cmd += [os.path.join(td, 'ro.o'), os.path.join(td, 'pad.o')]
        else: cmd.append(obj)
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode: print(r.stderr[:2000]); sys.exit(1)
        ob, osecs, osyms, _ = elf(out)
        # LSDA pointers (zPL FDEs) solve the .gcc_except_table base the same way.
        get = next((s for n, s in osecs if n == '.gcc_except_table'), None)
        eh = next((s for n, s in osecs if n == '.eh_frame'), None)
        if get and eh:
            ours = fdes(ob[eh[4]:eh[4] + eh[5]]); theirs = fdes(orig[EH[1]:EH[1] + EH[2]])
            deltas = {struct.unpack_from('<I', theirs[pc], 17)[0] - struct.unpack_from('<I', f, 17)[0]
                      for pc, f in ours.items() if f[16] == 4 and f[17:21] != bytes(4) and pc in theirs and theirs[pc][16] == 4}
            if len(deltas) > 1: conflicts.append(('.gcc_except_table', *map(hex, deltas)))
            elif deltas and deltas != {0}:
                cmd.insert(-1, '--section-start=.gcc_except_table=%#x' % (get[3] + deltas.pop()))
                r = subprocess.run(cmd, capture_output=True, text=True)
                if r.returncode: print(r.stderr[:2000]); sys.exit(1)
                ob, osecs, osyms, _ = elf(out)
        if os.environ.get('KEEP'): open(os.environ['KEEP'], 'wb').write(ob)   # the placed link, for inspection
        ok = True
        dropped = set()                                                     # pcs of discarded copies
        for n, s in osecs:
            if (n not in OSEC and not n.startswith('.lo.')) or s[1] != 1 or s[5] == 0: continue
            lo, fo, sz = OSEC['.text' if n.startswith('.lo.') else n]
            ours = ob[s[4]:s[4] + s[5]]; va = s[3]
            # an earlier TU's copy comes first in link order, so the link discards this one
            if n.startswith('.lo.') and n not in own and va < text_va:
                print(f'{n} {va:#010x}: discarded, the earlier copy is kept'); dropped.add(va); continue
            if not (lo <= va and va + len(ours) <= lo + sz):
                print(f'{n:8s} {va:#010x} size {len(ours):#7x}: outside the original section'); ok = False; continue
            theirs = orig[fo + va - lo:fo + va - lo + len(ours)]
            diff = [i for i in range(len(ours)) if ours[i] != theirs[i]]
            status = 'MATCH' if not diff else f'{len(diff)} bytes differ, first at +{diff[0]:#x}'
            ok &= not diff
            print(f'{n:8s} {va:#010x} size {len(ours):#7x}: {status}')
            if diff and verbose:
                fn = sorted((v, nm) for nm, v, sz, inf, sh in osyms if inf & 0xf == 2 and va <= v < va + len(ours))
                runs = []
                for d in diff:
                    if runs and d - runs[-1][1] <= 8: runs[-1][1] = d
                    else: runs.append([d, d])
                for a, e in runs[:12]:
                    at = va + a; owner = max((f for f in fn if f[0] <= at), default=(va, n))
                    print(f'   {at:#x} {owner[1]}+{at - owner[0]:#x} ({e - a + 1} B)')
                    i = a & ~15
                    print('     ours  ', ours[i:i + 32].hex(' '))
                    print('     theirs', theirs[i:i + 32].hex(' '))
        eh = next((s for n, s in osecs if n == '.eh_frame'), None)
        if eh:
            # the link drops a discarded copy's FDE along with its code
            ours = {pc: f for pc, f in fdes(ob[eh[4]:eh[4] + eh[5]]).items() if pc not in dropped}
            theirs = fdes(orig[EH[1]:EH[1] + EH[2]])
            lo, hi = text_va, end
            want = {pc for pc in theirs if lo <= pc < hi}
            bad = sorted(pc for pc in set(ours) | want if ours.get(pc) != theirs.get(pc))
            ok &= not bad
            print(f'.eh_frame {len(ours)} FDEs (original {len(want)}): '
                  + ('MATCH' if not bad else f'{len(bad)} differ, first pc {bad[0]:#x}'))
            if bad and verbose:
                for pc in bad[:12]: print('   ', hex(pc), 'ours' if pc in ours else '-', 'theirs' if pc in theirs else '-')
        bss = next((s for n, s in osecs if n == '.bss'), None)
        if bss: print(f'.bss     {bss[3]:#010x} size {bss[5]:#7x}: layout only (no file bytes)')
        claims = {k: v for k, v in solved.items() if not k.startswith('.')}
        defined = {nm for nm, v, sz, inf, sh in syms if inf >> 4 == 1 and sh != 0 and nm}
        placed = [(lo, lo + sz) for lo, fo, sz in OSEC.values()]
        for nm, v, sz, inf, sh in osyms:                                    # global, defined here and placed
            if nm in defined and any(lo <= v < hi for lo, hi in placed): claims[nm] = v
        here = {v: nm for nm, v, sz, inf, sh in osyms if nm in defined and inf & 0xf == 2}
        for k, v in solved.items():                                         # an external may not land on a function defined here
            if not k.startswith('.') and k not in defined and v in here: conflicts.append((k, 'lands on', here[v], hex(v)))
        for k, v in claims.items():
            if k in ledger and ledger[k][0] != v and (k, '%#x here' % v, '%#x in %s' % ledger[k]) not in conflicts:
                conflicts.append((k, '%#x here' % v, '%#x in %s' % ledger[k]))
        if ok and not conflicts:
            json.dump(claims, open(me[:-2] + '.syms.json', 'w'), indent=0, sort_keys=True)
    for c in conflicts[:20]: print('conflict', *c)
    print('TU VERIFIED' if ok and not conflicts else 'TU NOT VERIFIED')

if __name__ == '__main__':
    main()
