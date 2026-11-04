# mp-1.0 — Call of Duty 2 multiplayer client 1.0, Windows (in progress)

Rebuilds `CoD2MP_s.exe`, the Call of Duty 2 1.0 multiplayer client for Windows (1,703,936 bytes, SHA-256 `8caf434c…900e`, see
[checksums.yml](checksums.yml)) from C/C++ source with the original compiler.

**Status: checkpoint, not yet identical.** 1,698,959 of 1,699,840 section bytes sit at the
same offset as retail (99.961%); 669 bytes still differ. The remaining differences are in a
handful of functions where the source shape is not yet found (register choices, instruction
order, stack slots). This README is updated when the binary matches.

## Source

| Path | Contents |
|---|---|
| `src/` | The complete source: every file the build compiles or includes |
| `src/tus.txt` | Translation units in link order, with per-file compiler flags |
| `src/unknown/` | Objects whose original source files are unknown (empty `/GL` objects the Rich header counts) |
| `tools/` | `shameter.py` (same-offset meter), `rsrc.py` (copies the icon resource from your exe) |
| `guidpin.c` | `LD_PRELOAD` shim: gives the linker's `UuidCreate` the retail PDB GUID |
| `postlink.pl` | One documented 2-byte patch retail received after linking (`mixerGetRecordLevel`) |

## Build

Needs Docker and a Wine image with Visual C++ .NET 2003 (`cl` 13.10.3077, `link` 7.10) named
`cod2-msvc71-vs2003-ft` (adds `faketime`, see `ft.Dockerfile`), a `vc70/` folder with
Visual C++ .NET 2002 `cl`/`lib` (the retail `mss32.lib` stub was built with it), `dsound.lib`,
and the Summer 2004 DirectX SDK `d3d9.lib`. Microsoft tools and libraries are not included.

Where to get them (Microsoft no longer sells these; you need your own licensed copies):

| Needed | Product | Source |
|---|---|---|
| `cl` 13.10.3077, `link` 7.10, `dsound.lib`, Platform SDK libs | Visual Studio .NET 2003 Professional (Visual C++ 7.1) | Archive.org [Disc 1](https://archive.org/details/X09-46364), [Disc 2](https://archive.org/details/X09-46368), [Prerequisites](https://archive.org/details/X09-46366); or Visual Studio subscription downloads |
| `vc70/cl.exe`, `vc70/lib.exe` | Visual Studio .NET 2002 Professional (Visual C++ 7.0) | Archive.org [Disc 1](https://archive.org/details/X08-65717), [Disc 2](https://archive.org/details/X08-65718) |
| `d3d9.lib` (import hint 9) | DirectX 9.0c SDK, Summer 2004 | Archive.org [dxsdk_sum2004](https://archive.org/details/dxsdk_sum2004). The [December 2004](https://archive.org/details/dxsdk_dec2004) SDK gives import hint 10 and does not match |

The compiler runs under Wine inside Docker; any 32-bit Wine image with the VS .NET 2003
`Vc7` folder copied in works, tagged `cod2-msvc71-vs2003` for `ft.Dockerfile`.

    make release ANCHOR=/path/to/CoD2MP_s.exe DXSDK=/path/to/dxsdk   # build/release/CoD2MP_s.exe
    make check   ANCHOR=/path/to/CoD2MP_s.exe DXSDK=/path/to/dxsdk   # meter + byte compare

`ANCHOR` is your own copy of the retail exe; the build reads only its icon resource.
The link runs under `faketime` at the retail timestamp so the header is reproducible.
