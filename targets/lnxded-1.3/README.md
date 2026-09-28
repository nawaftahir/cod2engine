# lnxded-1.3 — Linux dedicated server 1.3

Rebuilds `cod2_lnxded_1_3` (1,318,204 bytes, SHA-256 `05e774a3…a3a7`, see
[checksums.yml](checksums.yml)) byte for byte: 157 translation units of game code,
all 998,480 bytes of `.text` less the startup objects, every constant, initialized
datum, exception table and ELF structure.

The rebuilt binary is the original, so it runs as the original: it loads maps and
accepts 1.3 clients (protocol 118).

## Source

1.3 is built as a delta of [`lnxded-1.2c`](../lnxded-1.2c), itself a delta of
[`lnxded-1.0`](../lnxded-1.0). `src/` holds only the files that differ from 1.2c; every
other source and header comes from the nearest layer (1.3, then 1.2c, then 1.0).

The changes from 1.2c: the 1.3 version and protocol 118, whose 128 KB `MAX_MSGLEN`
enlarges `netchan_t`, `client_t`, the status and rcon buffers (now `LargeLocal`s) and
the large-local pool; 32-bit fragment offsets; size checks on out-of-band voice data;
`client_t` allocated without the extra `memset`; one `hunkusage.dat`; unterminated-copy
fixes for the PunkBuster GUIDs; `ClientCommand` formats its reply into a local buffer.

| Path | Contents |
|---|---|
| `src/<module>/` | 1.3 versions of changed files |
| `src/tus.txt` | Every TU in link order: `path  text-address  [extra flags]` |
| `imports/` | Stand-ins for the shared libraries, generated from the original's import table |
| `tools/` | Verification tools, as in 1.2c |

The compiler, startup objects and linker are part of the toolchain:
[`toolchains/linux-breezy`](../../toolchains/linux-breezy), built with breezy's glibc
security update (`cod2engine-linux-breezy-1.3`).

## Build

```sh
make                                   # build/cod2_lnxded_1_3
make check                             # SHA-256 against checksums.yml
make build/obj/server/sv_main_mp.o     # one TU
```

## Verify

With your own original binary in `../../binaries/linux/` (or `ANCHOR=<path>`), and
Python 3 plus binutils on the host:

```sh
make verify                            # every TU: prints TU VERIFIED or the difference
python3 tools/elfcmp.py ../../binaries/linux/cod2_lnxded_1_3 build/cod2_lnxded_1_3 -v
python3 tools/tu_cov.py                # .text covered by verified TUs
```

## Note

The notes of [`lnxded-1.2c`](../lnxded-1.2c/README.md#note) apply unchanged. The
unreferenced locals `pad`, `pad2` and `pad3` in the voice-data senders are sized
from the stack frame.
