# lnxded-1.3 — Linux dedicated server 1.3

Rebuilds `cod2_lnxded_1_3` (1,318,204 bytes, SHA-256 `05e774a3…a3a7`, see
[checksums.yml](checksums.yml)) byte for byte: 157 translation units of game code,
all 998,480 bytes of `.text` less the startup objects, every constant, initialized
datum, exception table and ELF structure.

The rebuilt binary is the original, so it runs as the original: it loads maps and
accepts 1.3 clients (protocol 118).

## Source

The changes from [1.2c](../lnxded-1.2c): the 1.3 version and protocol 118, whose 128 KB `MAX_MSGLEN`
enlarges `netchan_t`, `client_t`, the status and rcon buffers (now `LargeLocal`s) and
the large-local pool; 32-bit fragment offsets; size checks on out-of-band voice data;
`client_t` allocated without the extra `memset`; one `hunkusage.dat`; unterminated-copy
fixes for the PunkBuster GUIDs; `ClientCommand` formats its reply into a local buffer.

| Path | Contents |
|---|---|
| `src/<module>/` | The complete source: every file the build compiles or includes |
| `src/unknown/` | Storage-only objects whose original source files are unknown |
| `src/compat/` | Compiler shim |

The compiler, startup objects, libraries and linker are those of the toolchain image
([`toolchains/linux-breezy`](../../toolchains/linux-breezy)), built with breezy's glibc security update. The link is the original
`g++ -ldl -lpthread <objects>`.

## Build

```sh
make                                   # build/cod2_lnxded_1_3
make check                             # SHA-256 against checksums.yml
make build/obj/server/sv_main_mp.o     # one TU
```

The build runs inside the `cod2engine-linux-breezy-1.3` image and needs nothing else. The
[Makefile](Makefile) lists the sources in link order, which fixes where every function and
variable lands, and carries the few per-file flags.

## Verify

With your own original binary in `../../binaries/linux/` (or `ANCHOR=<path>`), and
Python 3 plus binutils on the host, after `make`:

```sh
../../tools/verify.sh                  # every TU: prints TU VERIFIED or the difference
python3 ../../tools/tu_verify.py build/verify/server_sv_main_mp.o 0x<address> -v
python3 ../../tools/elfcmp.py ../../binaries/linux/cod2_lnxded_1_3 build/cod2_lnxded_1_3 -v
python3 ../../tools/tu_cov.py          # .text covered by verified TUs
```

`verify.sh` takes each object's address from `build/link.map`. `tu_verify` places a TU at
that address and compares `.text`, `.rodata`, `.data`, `.gcc_except_table` and its
`.eh_frame` entries with the original; it prints `TU VERIFIED` only when all of them match.

## Note

The notes of [`lnxded-1.2c`](../lnxded-1.2c/README.md#note) apply unchanged. The
unreferenced locals `pad`, `pad2` and `pad3` in the voice-data senders are sized
from the stack frame.
