# CoD2MP_s.exe 1.3, built with Visual C++ .NET 2003 (cl 13.10.3077, /GL + link /LTCG).
#
#   make            build/CoD2MP_s.exe (development link)
#   make release    build/release/CoD2MP_s.exe (the retail link: fixed image, PDB record)
#   make check      release + compare with ANCHOR (your own copy of the retail exe)

IMAGE  := cod2-msvc71-vs2003-ft
OUT    := build/CoD2MP_s.exe
REL    := build/release/CoD2MP_s.exe
ANCHOR ?= CoD2MP_s.exe
# retail 1.3 CodeView PDB GUID in exe byte order; guidpin.c feeds it to UuidCreate
PDB_GUID := d63b22ed86b6044d8f11e90a07d878f0
# retail Direct3DCreate9 import hint is 9 = Summer/Oct 2004 d3d9.lib (dec2004 gives 10)
DXSDK  ?= sdk/sum2004

ifndef IN_IMAGE

$(OUT) all:
	@mkdir -p build && python3 tools/rsrc.py $(ANCHOR) build/cod2mp.ico
	@mkdir -p build/lib && cp -p $(DXSDK)/Lib/d3d9.lib build/lib/d3d9.lib
	@gcc -m32 -shared -fPIC -O2 -o build/guidpin.so guidpin.c
	docker run --rm -v $(CURDIR):/w -v $(CURDIR)/src:/builds/pc_1.3_1_1/pc/cod2src -w /w $(IMAGE) sh -c 'make -j$$(nproc) -k IN_IMAGE=1 $(OUT); s=$$?; chown -R $(shell id -u):$(shell id -g) build; exit $$s'

# Retail has a fixed image and a linker-generated CodeView/PDB record.
release:
	@mkdir -p build && python3 tools/rsrc.py $(ANCHOR) build/cod2mp.ico
	@mkdir -p build/lib && cp -p $(DXSDK)/Lib/d3d9.lib build/lib/d3d9.lib
	@gcc -m32 -shared -fPIC -O2 -o build/guidpin.so guidpin.c
	docker run --rm -v $(CURDIR):/w -v $(CURDIR)/src:/builds/pc_1.3_1_1/pc/cod2src -w /w $(IMAGE) sh -c 'make -j$$(nproc) -k IN_IMAGE=1 $(REL); s=$$?; chown -R $(shell id -u):$(shell id -g) build; exit $$s'
	@sha256sum $(REL) $(ANCHOR)

check: release
	python3 tools/shameter.py $(REL) $(ANCHOR) | tail -1
	cmp $(REL) $(ANCHOR)

clean:
	rm -rf build

.PHONY: $(OUT) all release check clean

else

TUS    := $(shell sed -e 's/\#.*//' src/tus.txt | awk 'NF{print $$1}')
OBJS   := $(patsubst %,build/obj/%.obj,$(basename $(TUS)))
LWOBJS := $(filter build/obj/libwww/%,$(OBJS))
EXEOBJS := $(filter-out build/obj/libwww/%,$(OBJS))
tuflags = $(shell awk '$$1=="$(1)"{sub(/\#.*/,"");$$1="";print}' src/tus.txt)
# TUs marked "#oc" in tus.txt build with OCFLAGS (Mac decompile draft headers)
OCTUS  := $(shell awk '/\#oc$$/{print $$1}' src/tus.txt)

CL     := wine /opt/msvc710/Vc7/bin/cl.exe
LINK   := wine /opt/msvc710/Vc7/bin/link.exe
RC     := wine /opt/msvc710/Vc7/bin/rc.exe
CFLAGS := /nologo /c /O2 /GL /MT /DNDEBUG /DWIN32 /FI.\\compat\\msvc71.h /I.\\compat\\include \
	/I.\\universal /I. /I.\\qcommon /I.\\game /I.\\server_mp /I.\\bgame /I.\\script /I.\\xanim \
	/I.\\stringed /I.\\speex /I.\\speex\\speex
# draft client layer from the Mac 1.3 decompile, on its own headers until ported
OCFLAGS := /nologo /c /O2 /GL /MT /TP /DNDEBUG /FIstdint.h /FImsvc_c89.h \
	/FImsvc_gcc_compat.h /FIwin32_compat.h /FIprocess.h /FIfloat.h /I.\\oc\\shims \
	/I.\\oc\\shims\\msvc /I.\\oc\\shims\\posix /I.\\oc /I.\\oc\\headers /DWIN32 /D_WIN32 /DW32_CLIENT \
	/D_GNU_SOURCE=1 /DWIN32_LEAN_AND_MEAN /DNOMINMAX /Disfinite=_finite /Dvsnprintf=_vsnprintf /Dsnprintf=_snprintf
LFLAGS := /nologo /LTCG /SAFESEH:NO /FORCE /OPT:NOREF /OPT:NOICF /FIXED:NO /SUBSYSTEM:WINDOWS /STACK:0x10000,0x1000 /MAP:build\\CoD2MP_s.map

win = $(subst /,\\,$(1))
# header dependencies from /showIncludes (system headers skipped)
deps = awk '/including file:/{sub(/.*including file: */,""); gsub(/\\/,"/"); if ($$0 ~ /^[zZ]:\/opt/) next; \
	sub(/^[zZ]:\/w\/src\//,"src/"); sub(/^(\.\/)+/,"src/"); while (sub(/\/[^\/.][^\/]*\/\.\.\//,"/")); \
	sub(/\/headers\/pc\//,"/headers/PC/"); sub(/\/headers\/mac\//,"/headers/Mac/"); \
	sub(/\/effectscore\//,"/EffectsCore/"); \
	print "$@: " $$0; print $$0 ":"}' $@.log > $@.d

-include $(OBJS:=.d)


build/obj/%.obj: src/%.cpp
	@mkdir -p $(dir $@)
	@cd src && $(CL) $(if $(filter $*.cpp,$(OCTUS)),$(OCFLAGS),$(CFLAGS)) $(call tuflags,$*.cpp) /showIncludes /Fo..\\$(call win,$@) .\\$(call win,$*.cpp) > ../$@.log 2>&1 || (grep -v including ../$@.log; false)
	@$(deps)

build/obj/%.obj: src/%.c
	@mkdir -p $(dir $@)
	@cd src && $(CL) $(CFLAGS) $(call tuflags,$*.c) /showIncludes /Fo..\\$(call win,$@) .\\$(call win,$*.c) > ../$@.log 2>&1 || (grep -v including ../$@.log; false)
	@$(deps)

IMPLIBS := build/lib/mss32.lib build/lib/d3d9.lib

# libwww TUs: __FILE__ must render exactly \builds\pc_1.3_1_1\pc\cod2src\... (retail strings),
# so cl gets the drive-relative source arg and a cmd batch that first parks the DOS cwd on that drive.
WCL      := wine cmd /c
CLDOS    := Z:/opt/msvc710/Vc7/bin/cl.exe
WFLAGS   := /nologo /c /O2 /MT /DNDEBUG /DWIN32 /D_WINDOWS /I\builds\pc_1.3_1_1\pc\cod2src\libwww\Library\src

build/obj/libwww/%.obj: src/libwww/%.c src/libwww/Library/src/windows/config.h $(wildcard src/libwww/Library/src/*.h)
	@mkdir -p $(dir $@)
	@printf '%s\r\n' '@echo off' 'cd \builds\pc_1.3_1_1\pc' \
		'$(subst /,\,$(CLDOS)) $(WFLAGS) $(call tuflags,libwww/$*.c) /showIncludes /Fo$(subst /,\,Z:/w/$@) \builds\pc_1.3_1_1\pc\cod2src\$(subst /,\,libwww/$*.c)' \
		> $@.bat
	@$(WCL) '$(subst /,\,Z:/w/$@.bat)' > $@.log 2>&1 || (grep -v including $@.log; rm -f $@; false)
LIBS   := winmm.lib wsock32.lib $(call win,$(IMPLIBS)) dsound.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib $(call win,build/lib/libwww.lib) libcmt.lib

# retail links libwww as an archive after the import libs: its members land after the import thunks, before libcmt
build/lib/libwww.lib: $(LWOBJS) src/tus.txt
	@mkdir -p $(dir $@)
	@printf '%s\n' $(call win,$(LWOBJS)) > build/lw.rsp
	@wine /opt/msvc710/Vc7/bin/lib.exe /nologo /out:$(call win,$@) @build\\lw.rsp > $@.log 2>&1 || (cat $@.log; false)

build/lib/%.lib: src/lib/%.def src/lib/impname.pl
	@mkdir -p $(dir $@)
	@wine /opt/msvc710/Vc7/bin/lib.exe /nologo /machine:x86 /def:$(call win,$<) /out:$(call win,$@) > $@.log 2>&1 || (cat $@.log; false)
	@perl src/lib/impname.pl $@ 3 >> $@.log

# the retail mss32.lib (MSS_auto_cleanup + imports) was built with VS .NET 2002 (7.00.9466), local copy in vc70/ (not in git)
build/lib/mss_auto.obj: src/lib/mss_auto.c
	@mkdir -p $(dir $@)
	@cd src && wine ../vc70/cl.exe /nologo /c /O2 /MT /DNDEBUG /Fo..\\build\\lib\\mss_auto.obj lib\\mss_auto.c > ../$@.log 2>&1 || (cat ../$@.log; false)

# second plain lib pass puts mss_auto.obj before the import descriptor (retail Rich order)
build/lib/mss32.lib: src/lib/mss32.def build/lib/mss_auto.obj src/lib/impname.pl
	@wine vc70/lib.exe /nologo /machine:x86 /def:$(call win,$<) /out:build\\lib\\mss32_imp.lib > $@.log 2>&1 || (cat $@.log; false)
	@perl src/lib/impname.pl build/lib/mss32_imp.lib 1 >> $@.log
	@wine vc70/lib.exe /nologo /out:build\\lib\\mss32_1.lib build\\lib\\mss32_imp.lib build\\lib\\mss_auto.obj >> $@.log 2>&1 || (cat $@.log; false)
	@wine vc70/lib.exe /nologo /out:$(call win,$@) build\\lib\\mss32_1.lib >> $@.log 2>&1 || (cat $@.log; false)

# icon comes from the local retail exe (host step above); .rsrc is byte-identical to retail
build/cod2mp.res: src/cod2mp.rc build/cod2mp.ico
	@cd src && $(RC) /l 0x409 /fo..\\build\\cod2mp.res cod2mp.rc > ../$@.log 2>&1 || (cat ../$@.log; false)

$(OUT): $(EXEOBJS) build/lib/libwww.lib $(IMPLIBS) build/cod2mp.res src/tus.txt
	@printf '%s\n' $(call win,$(EXEOBJS)) > build/objs.rsp
	$(LINK) $(LFLAGS) /OUT:$(call win,$@) @build\\objs.rsp build\\cod2mp.res $(LIBS) > build/link.log 2>&1; tail -1 build/link.log

$(REL): $(EXEOBJS) build/lib/libwww.lib $(IMPLIBS) build/cod2mp.res src/tus.txt Makefile
	@mkdir -p $(dir $@)
	@mkdir -p "$$(winepath -u 'c:\builds\pc_1.3_1_1\pc\cod2\pc')"
	@printf '%s\n' $(call win,$(EXEOBJS)) > build/objs.rsp
	wineserver -k 2>/dev/null; export FAKETIME='2006-05-02 00:09:51' GUIDPIN=$(PDB_GUID) LD_PRELOAD="$(wildcard /usr/lib/*/faketime/libfaketime.so.1) $(CURDIR)/build/guidpin.so"; $(LINK) $(subst /FIXED:NO,/FIXED,$(subst build\\CoD2MP_s.map,build\\release\\CoD2MP_s.map,$(LFLAGS))) /DEBUG '/PDB:c:\builds\pc_1.3_1_1\pc\cod2\pc\CoD2MP_s.pdb' /OUT:$(call win,$@) @build\\objs.rsp build\\cod2mp.res $(LIBS) > build/release/link.log 2>&1 || { tail -10 build/release/link.log; exit 1; }
	@! grep -E 'LNK2001|LNK2019|fatal error' build/release/link.log
	@true # 1.0-only mixerGetRecordLevel postlink is disabled for 1.3
	@cp "$$(winepath -u 'c:\builds\pc_1.3_1_1\pc\cod2\pc\CoD2MP_s.pdb')" build/release/CoD2MP_s.pdb

endif
