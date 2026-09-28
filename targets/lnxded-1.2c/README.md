# lnxded-1.2c — Linux dedicated server 1.2c

Rebuilds `cod2_lnxded_1_2c` (1,318,172 bytes, SHA-256 `d6746a17…2b2b`, see
[checksums.yml](checksums.yml)) byte for byte: 157 translation units of game code,
all 998,112 bytes of `.text` less the startup objects, every constant, initialized
datum, exception table and ELF structure.

The rebuilt binary is the original, so it runs as the original: it loads maps and
accepts 1.2 clients (protocol 117).

## Source

1.2c is built as a delta of [`lnxded-1.0`](../lnxded-1.0). `src/` holds only the files
that differ; every other source and header comes from `../lnxded-1.0/src`. A header
copied into `src/` overrides the 1.0 one for every TU (`-I-`).

The main changes from 1.0: the 1.2 version and protocol, the critical sections around
the log file, errors, dvars and redirected output, Czech as a fifteenth language, GBK
ranges for Chinese, PunkBuster (`src/punkbuster/`, `dvar_cmds.cpp`), a Bison 2.0
script parser, and the new server and game features of the 1.2 patch.

| Path | Contents |
|---|---|
| `src/<module>/` | 1.2c versions of changed files, and new files |
| `src/tus.txt` | Every TU in link order: `path  text-address  [extra flags]` |
| `src/unknown/` | Storage-only objects whose original source files are unknown |
| `imports/` | Stand-ins for the shared libraries, generated from the original's import table |
| `tools/` | Verification tools |

The compiler, startup objects and linker are part of the toolchain:
[`toolchains/linux-breezy`](../../toolchains/linux-breezy).

## Build

```sh
make                                   # build/cod2_lnxded_1_2c
make check                             # SHA-256 against checksums.yml
make build/obj/server/sv_main_mp.o     # one TU
```

The build runs inside the `cod2engine-linux-breezy` image and needs nothing else.

## Verify

With your own original binary in `../../binaries/linux/` (or `ANCHOR=<path>`), and
Python 3 plus binutils on the host:

```sh
make verify                            # every TU: prints TU VERIFIED or the difference
python3 tools/elfcmp.py ../../binaries/linux/cod2_lnxded_1_2c build/cod2_lnxded_1_2c -v
python3 tools/tu_cov.py                # .text covered by verified TUs
```

The tools work as in [`lnxded-1.0`](../lnxded-1.0/README.md#verify).

## Note

- **Unknown names.** Storage-only objects (`src/unknown/`) and unreferenced variables
  have no references left in the binary. Their sizes and positions are fixed by the
  layout; their names are neutral placeholders.
- **Unrecovered constructs.** `SV_DirectConnect` has a dead `guid` test that only a
  register-to-register body reproduces at `-O0`; the original statement is unknown and
  the comment there says so. `Scr_ReadTsc` reads the time-stamp counter with a
  one-instruction `rdtsc` inline assembly.
