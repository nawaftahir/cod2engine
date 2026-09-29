# lnxded-1.0 — Linux dedicated server 1.0

Rebuilds `cod2_lnxded_1_0a` (1,305,356 bytes, SHA-256 `35c88f18…f938`, see
[checksums.yml](checksums.yml)) byte for byte: 155 translation units of game code,
all 980,640 bytes of `.text`, every constant, initialized datum, exception table and
ELF structure.

The rebuilt binary is the original, so it runs as the original: it loads maps, accepts
1.0 clients and plays normally.

## Layout

| Path | Contents |
|---|---|
| `src/<module>/` | One translation unit per original source file, headers beside them |
| `src/unknown/` | Storage-only objects whose original source files are unknown |
| `tools/` | Verification tools (`make verify`) |
| `src/compat/` | Compiler shim and the libc declarations as the original build saw them |
| `imports/` | Stand-ins for the shared libraries, generated from the original's import table (`tools/implib.py`) |

The startup objects and the linker are part of the toolchain:
[`archive/toolchains/linux-2005`](../toolchains/linux-2005). The imports and the reconstructed
startup objects stand in for the Red Hat 6-era glibc 2.1 the original was linked against;
replacing them with that glibc is open (see `../../PLAN.md`).

## Build

```sh
make                                   # build/cod2_lnxded_1_0a
make check                             # SHA-256 against checksums.yml
make build/obj/server/sv_main_mp.o     # one TU
```

The build runs inside the `cod2engine-linux-2005` image and needs nothing else. The
[Makefile](Makefile) lists the sources in link order, which fixes where every function and
variable lands, and carries the few per-file flags.

## Verify

With your own original binary in `../../binaries/linux/` (or `ANCHOR=<path>`), and
Python 3 plus binutils on the host, after `make`:

```sh
make verify                            # every TU: prints TU VERIFIED or the difference
python3 tools/tu_verify.py build/verify/server_sv_main_mp.o 0x<address> -v
python3 tools/elfcmp.py ../../binaries/linux/cod2_lnxded_1_0a build/cod2_lnxded_1_0a -v
python3 tools/tu_cov.py          # .text covered by verified TUs
```

`tools/verify.sh` takes each object's address from `build/link.map`. `tu_verify` places a TU at
that address and compares `.text`, `.rodata`, `.data`, `.gcc_except_table` and its
`.eh_frame` entries with the original; it prints `TU VERIFIED` only when all of them match.

## Caveats

- **Unknown names.** 16 storage-only objects (`src/unknown/`), a few unreferenced tail
  variables and the 1 KB build-info buffer have no references left in the binary. Their
  sizes and positions are fixed by the layout; their names are neutral placeholders.
- **Unrecovered constructs.** A few functions keep decompiler-style local names. One
  function (`G_Damage`) needs a dead `register long long` to reproduce the original
  control flow; the comment there explains why.
