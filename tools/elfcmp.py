#!/usr/bin/env python3
# Section-by-section comparison of a linked ELF with the anchor.
# usage: tools/elfcmp.py ANCHOR LINKED [-v]
import struct, sys

def load(path):
    b = open(path, 'rb').read()
    shoff, = struct.unpack_from('<I', b, 0x20)
    shnum, shstrndx = struct.unpack_from('<HH', b, 0x30)
    sh = [struct.unpack_from('<10I', b, shoff + i * 40) for i in range(shnum)]
    strs = sh[shstrndx]
    name = lambda o: b[strs[4] + o:b.index(b'\0', strs[4] + o)].decode()
    return b, [(name(s[0]),) + s for s in sh]

a, asec = load(sys.argv[1])
b, bsec = load(sys.argv[2])
verbose = '-v' in sys.argv
print('file size', len(a), len(b), 'same' if len(a) == len(b) else 'DIFF')
print('ELF header', 'same' if a[:0x34] == b[:0x34] else 'DIFF')
phoff, = struct.unpack_from('<I', a, 0x1c); phn, = struct.unpack_from('<H', a, 0x2c)
print('program headers', 'same' if a[phoff:phoff + phn * 32] == b[phoff:phoff + phn * 32] else 'DIFF')
bmap = {s[0]: s for s in bsec}
for s in asec:
    n, _, typ, flags, addr, off, size = s[:7]
    t = bmap.get(n)
    if t is None:
        print('%-18s missing' % n); continue
    hdr = [] if (addr, size) == (t[4], t[6]) else ['addr %#x/%#x size %#x/%#x' % (addr, t[4], size, t[6])]
    if typ == 8:  # NOBITS
        print('%-18s %s' % (n, 'same' if not hdr and off == t[5] else 'DIFF ' + ' '.join(hdr) + ' off %#x/%#x' % (off, t[5])))
        continue
    x, y = a[off:off + size], b[t[5]:t[5] + t[6]]
    diff = [i for i in range(min(len(x), len(y))) if x[i] != y[i]]
    st = 'same' if x == y and off == t[5] else 'DIFF %d bytes%s%s' % (
        len(diff), ', first +%#x (%#x)' % (diff[0], addr + diff[0]) if diff else '', ', off %#x/%#x' % (off, t[5]) if off != t[5] else '')
    print('%-18s %s %s' % (n, st, ' '.join(hdr)))
    if verbose and diff:
        i = diff[0] & ~15
        print('    anchor', x[i:i + 32].hex(' ')); print('    linked', y[i:i + 32].hex(' '))
for n in bmap.keys() - {s[0] for s in asec}:
    print('%-18s extra in linked' % n)
