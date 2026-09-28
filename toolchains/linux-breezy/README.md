# linux-breezy — the Linux 1.2c/1.3 build system

A Docker image of the machine the Linux server 1.2c and 1.3 binaries were built on:
Ubuntu 5.10 "breezy", i386, installed from `old-releases.ubuntu.com` with `debootstrap`.
Unlike [`linux-2005`](../linux-2005), nothing is rebuilt from source: every piece is a
stock breezy package, pinned by version.

| Piece | Package | Owner |
|---|---|---|
| gcc/g++ 3.3.6 | `gcc-3.3`, `g++-3.3` 1:3.3.6-8ubuntu1 | the game code |
| `crtbegin.o`, `crtend.o` | `gcc-3.3` (`/usr/lib/gcc-lib/i486-linux-gnu/3.3.6/`) | the compiler |
| `crt1.o`, `crti.o`, `crtn.o`, `libc_nonshared.a` | `libc6-dev` 2.3.5-1ubuntu12 for 1.2c, 2.3.5-1ubuntu12.5.10.1 for 1.3 (both built with gcc 3.4.5) | the C library |
| `ld` 2.16.1 | `binutils` 2.16.1-2ubuntu6 | the linker |

```sh
docker build --platform linux/386 -t cod2engine-linux-breezy toolchains/linux-breezy
docker build --platform linux/386 --build-arg LIBC6=2.3.5-1ubuntu12.5.10.1 \
    -t cod2engine-linux-breezy-1.3 toolchains/linux-breezy
```

The build fails if the installed versions differ from the pinned ones.

## Evidence

| In the binary | What it proves |
|---|---|
| `.comment`: `GCC: (GNU) 3.3.6 (Ubuntu 1:3.3.6-8ubuntu1)` ×159 | game code, `crtbegin` and `crtend` built by breezy's gcc-3.3 |
| `.comment`: `GCC: (GNU) 3.4.5 20050809 (prerelease) (Ubuntu 3.4.4-6ubuntu8)` ×4 | `crt1`, `crti`, `crtn` and `libc_nonshared`'s `elf-init` from breezy's glibc 2.3.5 build |
| `.eh_frame` uses relaxed `DW_CFA_advance_loc` | no `--traditional-format`, unlike 1.0 |
| `.eh_frame_hdr` / `PT_GNU_EH_FRAME` | the driver passed `--eh-frame-hdr` |
| 1.3's `crti`/`crtn` take the GOT address with `call`/`pop`, not `__i686.get_pc_thunk.bx` | 1.3 was linked after breezy's glibc security update, whose startup objects were built that way |
| the rebuilt file is SHA-256 identical | ld 2.16.1 with this link line reproduces every ELF structure |

## Link

```
crt1.o crti.o crtbegin.o  libdl libpthread  <game objects>  libstdc++ libm libgcc_s libc
libc_nonshared.a  crtend.o crtn.o
```

The same order as 1.0, plus `libc_nonshared.a`, which glibc 2.3 adds to every link.
