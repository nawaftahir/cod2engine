# lnxded-1.0 — Linux dedicated server 1.0

Rebuilds `cod2_lnxded_1_0a` (1,305,356 bytes, SHA-256 `35c88f18…f938`, see
[checksums.yml](checksums.yml)) byte for byte: 157 translation units, all 980,640 bytes
of `.text`, every constant, initialized datum, exception table and ELF structure.

The rebuilt binary is the original, so it runs as the original: it loads maps, accepts
1.0 clients and plays normally.

## Layout

| Path | Contents |
|---|---|
| `src/<module>/` | One translation unit per original source file, headers beside them |
| `src/tus.txt` | Every TU in link order: `path  text-address  [extra flags]` |
| `src/crt/` | Startup files: glibc 2.1 `crt1`, egcs 1.1.2 `crti`/`crtn`, gcc 3.3.4 `crtbegin`/`crtend` |
| `src/unknown/` | Storage-only objects whose original source files are unknown |
| `src/compat/` | Compiler shim and the libc declarations as the original build saw them |
| `tools/` | Build, verify and link scripts |

## Build

From this directory, after the toolchain image is built (see the top-level README):

```sh
sh tools/build_ld.sh                         # once: binutils 2.14.90.0.6 ld
bash tools/tu_all.sh                         # build + verify all TUs
sh tools/link.sh                             # link, compare SHA-256
```

One TU at a time:

```sh
sh tools/tu_build.sh src/server/sv_main_mp.cpp           # -> build/tu/sv_main_mp.o
python3 tools/tu_verify.py build/tu/sv_main_mp.o 0x<VA> -v
python3 tools/elfcmp.py ../../binaries/linux/cod2_lnxded_1_0a build/cod2_lnxded_1_0a -v
```

`tu_verify` places a TU at its original address and compares `.text`, `.rodata`,
`.data`, `.gcc_except_table` and its `.eh_frame` entries; it prints `TU VERIFIED` only
when all of them match. The anchor path can be overridden with `ANCHOR=`.

## Toolchain

| Piece | Version | Evidence |
|---|---|---|
| Compiler | FSF gcc/g++ 3.3.4, `-O0` | `.comment` reads `GCC: (GNU) 3.3.4` ×157 |
| gcc configure | without `HAVE_AS_LEB128` | `.gcc_except_table` uses udata4 call sites |
| Assembler | GNU as, `--traditional-format` | FDEs use `DW_CFA_advance_loc4` |
| Linker | H.J. Lu binutils 2.14.90.0.6 | has `PT_GNU_STACK` (2003-06) yet keeps PLT values in `.dynsym` (dropped 2003-11) |
| Link order | `g++ -ldl -lpthread <objects>` | `.dynstr` order of the imported names |
| Libraries | glibc 2.1, libstdc++.so.5 | symbol versions in `.gnu.version_r` |

The link uses stub libraries generated from the binary's own import table
(`tools/implib.py`); only names, versions and sizes are needed.

## Caveats

- **Unknown names.** 16 storage-only objects (`src/unknown/`), a few unreferenced tail
  variables and the 1 KB build-info buffer have no references left in the binary. Their
  sizes and positions are fixed by the layout; their names are neutral placeholders.
- **egcs startup files.** `crti.S`, `crtn.S` and `init.S` are the assembly egcs 1.1.2
  emitted for them. That compiler is not part of the toolchain image.
- **Unrecovered constructs.** A few functions keep decompiler-style local names. One
  function (`G_Damage`) needs a dead `register long long` to reproduce the original
  control flow; the comment there explains why.
