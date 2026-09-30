> **Work in progress.**

A byte-accurate reconstruction of the Call of Duty 2 engine source.

## Status

| Target | Binary | Compiler | State |
|---|---|---|---|
| `archive/lnxded-1.0` | Linux dedicated server 1.0 | GCC 3.3.4 | SHA-identical |
| `archive/lnxded-1.2c` | Linux dedicated server 1.2c | GCC 3.3.6 | SHA-identical |
| `archive/lnxded-1.3` | Linux dedicated server 1.3 | GCC 3.3.6 | SHA-identical |

## Building

Each target builds inside its pinned toolchain image (`archive/toolchains/`). You supply the
original binary yourself in `binaries/linux/`; it is used only for verification and is never
distributed.

```
cd archive/lnxded-1.3
make toolchain   # build the toolchain image
make check       # build and compare SHA-256 with the original
make verify      # compare every translation unit
```

See each target's `README.md` for details.

## References

- [CoD2rev_Server](https://github.com/voron00/CoD2rev_Server): the server decompilation this work builds on
- [Quake III Arena](https://github.com/id-Software/Quake-III-Arena): id Software's GPL release, the engine's ancestor
- [opencod2](https://github.com/opencod2/opencod2)
- [KisakCOD](https://github.com/SwagSoftware/KisakCOD)
- [cod2-mp-macho](https://github.com/yctn/cod2-mp-macho): the Mac 1.3 client, whose debug info supplies names and types

## Acknowledgements

Thanks to the authors of the projects above, and to the CoD2 community (CoD2_Rev,libcod) for years of prior work.

Call of Duty is a trademark of Activision. This project is not affiliated with or endorsed by
Activision or Infinity Ward, and it ships no game assets or original binaries. You need your own
copy of the game.
