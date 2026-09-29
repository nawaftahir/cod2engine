# linux-2005 — the original Linux build system

A Docker image that reproduces the machine the Linux server binaries were built on,
as far as the binaries record it. It holds three things:

| Piece | Where | Owner |
|---|---|---|
| gcc/g++ 3.3.4 | `/usr/local/bin/gcc`, `g++` | the compiler |
| binutils 2.14.90.0.6 `ld` | `/opt/binutils-2.14.90.0.6/bin/ld` | the linker |
| startup objects | `/opt/crt-2005/*.o`, built from [`crt/`](crt) | the C library and the compiler |

```sh
docker build --platform linux/386 -t cod2engine-linux-2005 archive/toolchains/linux-2005
```

All sources are downloaded from GNU and kernel.org mirrors and checked against pinned
SHA-256 sums. The host system is Debian sarge, which also provides GNU as 2.15.

## Evidence

Every piece is pinned by something the original binary records about its own build:

| In the binary | What it proves |
|---|---|
| `.comment`: `GCC: (GNU) 3.3.4` ×157 | the game code was built with plain FSF gcc 3.3.4 |
| `.gcc_except_table` call sites use udata4 (encoding `0x03`) | that gcc was configured on a system whose assembler lacked `.uleb128` (binutils < 2.11), so `HAVE_AS_LEB128` is off |
| `.eh_frame` uses `DW_CFA_advance_loc4` | the assembler ran with `--traditional-format` |
| `PT_GNU_STACK` present, PLT addresses kept in `.dynsym` | a linker between 2003-06 and 2003-11: H.J. Lu's binutils 2.14.90.0.6 |
| `.gnu.version_r`: `GLIBC_2.0`, `GLIBC_2.1` | built against glibc 2.1 |
| `.comment`: `egcs-2.91.66` ×3, `.note` `01.01` ×3 | glibc's startup objects were compiled by egcs 1.1.2 (Red Hat 6.x) |

The build machine was a Red Hat 6-era system (glibc 2.1, egcs 1.1.2) with gcc 3.3.4
and a 2003 linker installed on top.

## Startup objects (`crt/`)

Every Linux program contains a few small objects the compiler driver adds on its own:
the entry point, the `.init`/`.fini` sections that run constructors and destructors,
and the frame-info registration for C++ exceptions. They are not game code, but their
bytes are in the binary, and they depend on the system they were built on. The ones
installed with this image's gcc come from a newer system and produce a different file,
so the 2005 ones are rebuilt here.

| File | Becomes | Upstream source | Why this form |
|---|---|---|---|
| `start.S` | `crt1.o` | glibc `sysdeps/i386/elf/start.S` | assembly upstream: `_start` runs before a stack frame exists |
| `abi-note.S` | `crt1.o` | glibc `csu/abi-note.S` | assembly upstream: an ELF note, not code |
| `init.S` | `crt1.o` | glibc 2.1 `csu/init.c` | egcs 1.1.2 output; egcs is not in the image |
| `crti.S`, `crtn.S` | `crti.o`, `crtn.o` | glibc 2.1 `csu/initfini.c` | glibc's own build compiles `initfini.c` to assembly and splits it in two; the egcs 1.1.2 output is kept |
| `crtbegin.c`, `crtend.c` | `crtbegin.o`, `crtend.o` | gcc 3.3.4 `gcc/crtstuff.c` | C, reduced to the i386-linux configuration; the inline assembly is gcc's own |

The link puts them around the game objects:

```
crt1.o crti.o crtbegin.o  libdl libpthread  <game objects>  libstdc++ libm libgcc_s libc  crtend.o crtn.o
```

At run time the kernel loads the program and `ld-linux.so.2` loads the libraries, then
`_start` calls `__libc_start_main`, which runs `_init` (crti, crtbegin and crtend's
`.init` pieces, crtn) and then `main`.

## Modern builds

None of this is needed to build the game with a current compiler: every modern
toolchain supplies its own startup objects, linker and C library. What carries over is
the knowledge of what they do, in case a port has to reproduce their behavior.
