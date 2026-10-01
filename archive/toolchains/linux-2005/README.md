# linux-2005 — the original Linux build system

A Docker image that reproduces the machine the Linux server 1.0 binary was built on, as far as
the binary records it: Red Hat Linux 6.0 with gcc 3.3.4 and binutils 2.14.90.0.x installed on top.
Everything in the build is the real thing — the system's own C library, startup objects and
shared libraries, and a compiler and linker built from their release sources.

```sh
docker build --platform linux/386 --build-arg JOBS=$(nproc) -t cod2engine-linux-2005 archive/toolchains/linux-2005
```

| Piece | Where | Source |
|---|---|---|
| Red Hat Linux 6.0 base (glibc 2.1.1-6, egcs 1.1.2, make, bash…) | `/` | RPMs from the release CD ([`rpms.txt`](rpms.txt)) |
| gcc/g++ 3.3.4, libstdc++.so.5, libgcc_s.so.1 | `/usr/local` | gnu.org, built in the image |
| ld 2.14.90.0.6 | `/usr/local/bin/ld` | kernel.org, built in the image |
| as 2.14.90.0.8 | `/usr/local/bin/as` | kernel.org, built in the image |

Every download is checked against a pinned SHA-256. The Red Hat packages are read out of the
6.0 CD image on archive.org (`PCP_0699`, "Red Hat Linux/i386 6.0", 1999-04-20) by byte range,
so only the 28 packages the build needs are fetched.

## Evidence

Every piece is pinned by something the original binary records about its own build:

| In the binary | What it proves |
|---|---|
| `.comment`: `GCC: (GNU) 3.3.4` ×157 | the game code was built with plain FSF gcc 3.3.4 |
| `.comment`: `egcs-2.91.66` ×3, `.note` `01.01` ×3 | crt1/crti/crtn came from a Red Hat 6.x glibc |
| sizes of the 141 imported glibc symbols | exactly glibc 2.1.1-6 (Red Hat 6.0); 6.1 differs in 13, 6.2 in 16 |
| `fileno` is 24 bytes | glibc 2.1.1 only (2.1.2 added errno handling) |
| no exception tables around libc calls | 2.1.1's `sys/cdefs.h` adds `throw()` only for gcc minor ≥ 8, so gcc 3.3 saw none |
| `.gcc_except_table` call sites use udata4 | gcc was configured with an assembler lacking `.uleb128` (Red Hat's as 2.9.1), so `HAVE_AS_LEB128` is off |
| `.eh_frame` uses `DW_CFA_advance_loc4` | the same configure put `--traditional-format` in gcc's assembler spec |
| local statics in `.bss` order | gas 2.14.90.0.8 or later (earlier versions order them differently) |
| `PT_GNU_STACK`, PLT addresses in `.dynsym`, no `.eh_frame_hdr` | ld 2.14.90.0.6, run without `--eh-frame-hdr` |
| `GLIBCPP_3.2`, `CXXABI_1.2` import versions | libstdc++ was built with that ld on PATH |

## Running 1999 userland on a current kernel

Three Red Hat 6.0 tools misbehave here; the image and Makefiles work around them:

- `tar z` hangs waiting for `gzip`: the sources are unpacked in the fetch stage instead.
- `bash` 1.14 can miss a child's exit and hang: make recipes avoid the shell (no shell syntax),
  and object directories are made once while make reads the Makefile.
- `as` 2.9.1 marks gcc 3.3's `.debug_*` sections allocatable, which breaks shared-library links:
  the toolchain is built without debug info (`LIBGCC2_DEBUG_CFLAGS = -g0`). This changes no code.

## The link

The original was linked with `g++ -ldl -lpthread <objects>`. The gcc driver built here adds
`--eh-frame-hdr` (configure found ld 2.14), which the original lacks, so the target's Makefile
runs the expanded `ld` command instead:

```
crt1.o crti.o crtbegin.o  -ldl -lpthread  <game objects>  -lstdc++ -lm -lgcc_s -lgcc -lc  crtend.o crtn.o
```

At run time the kernel loads the program and `ld-linux.so.2` loads the libraries, then `_start`
(crt1) calls `__libc_start_main`, which runs `_init` (crti, crtbegin, crtend, crtn) and `main`.
