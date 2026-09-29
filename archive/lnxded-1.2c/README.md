# lnxded-1.2c — Linux dedicated server 1.2c

Rebuilds `cod2_lnxded_1_2c` (1,318,172 bytes, SHA-256 `d6746a17…2b2b`, see
[checksums.yml](checksums.yml)) byte for byte: 157 translation units of game code,
all 998,112 bytes of `.text` less the startup objects, every constant, initialized
datum, exception table and ELF structure.

The rebuilt binary is the original, so it runs as the original: it loads maps and
accepts 1.2 clients (protocol 117).

## Source

The main changes from [1.0](../lnxded-1.0): the 1.2 version and protocol, the critical sections around
the log file, errors, dvars and redirected output, Czech as a fifteenth language, GBK
ranges for Chinese, PunkBuster (`src/punkbuster/`, `dvar_cmds.cpp`), a Bison 2.0
script parser, and the new server and game features of the 1.2 patch.

| Path | Contents |
|---|---|
| `src/<module>/` | The complete source: every file the build compiles or includes |
| `src/unknown/` | Storage-only objects whose original source files are unknown |
| `src/compat/` | Compiler shim |

The compiler, startup objects, libraries and linker are those of the toolchain image
([`toolchains/linux-breezy`](../../toolchains/linux-breezy)). The link is the original
`g++ -ldl -lpthread <objects>`.

## Build

```sh
make                                   # build/cod2_lnxded_1_2c
make check                             # SHA-256 against checksums.yml
make build/obj/server/sv_main_mp.o     # one TU
```

The build runs inside the `cod2engine-linux-breezy` image and needs nothing else. The
[Makefile](Makefile) lists the sources in link order, which fixes where every function and
variable lands, and carries the few per-file flags.

## Verify

With your own original binary in `../../binaries/linux/` (or `ANCHOR=<path>`), and
Python 3 plus binutils on the host, after `make`:

```sh
../../tools/verify.sh                  # every TU: prints TU VERIFIED or the difference
python3 ../../tools/tu_verify.py build/verify/server_sv_main_mp.o 0x<address> -v
python3 ../../tools/elfcmp.py ../../binaries/linux/cod2_lnxded_1_2c build/cod2_lnxded_1_2c -v
python3 ../../tools/tu_cov.py          # .text covered by verified TUs
```

`verify.sh` takes each object's address from `build/link.map`. `tu_verify` places a TU at
that address and compares `.text`, `.rodata`, `.data`, `.gcc_except_table` and its
`.eh_frame` entries with the original; it prints `TU VERIFIED` only when all of them match.

## Note

- **Unknown names.** Storage-only objects (`src/unknown/`) and unreferenced variables
  have no references left in the binary. Their sizes and positions are fixed by the
  layout; their names are neutral placeholders.
- **Unrecovered constructs.** `SV_DirectConnect` has a dead `guid` test that only a
  register-to-register body reproduces at `-O0`; the original statement is unknown and
  the comment there says so. `Scr_ReadTsc` reads the time-stamp counter with a
  one-instruction `rdtsc` inline assembly.
