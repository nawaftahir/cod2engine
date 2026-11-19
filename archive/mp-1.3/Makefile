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

# Link order = retail order: under /LTCG it decides where every function and variable lands.
# unknown/: objects whose original source is unknown. unknown_b013f8.cpp sits where its code sits in the
# retail exe; empty_2..6 are empty objects that stand in for 6 more compiled files the retail link contains.
SRCS := \
	universal/assertive.cpp \
	qcommon/buildnumber.c \
	client_mp/cl_cgame_mp.cpp \
	client_mp/cl_cin_mp.cpp \
	client_mp/cl_console_mp.cpp \
	client_mp/cl_input.cpp \
	client_mp/cl_keys_mp.cpp \
	client_mp/cl_main_mp.cpp \
	client_mp/cl_devgui.cpp \
	client_mp/cl_net_chan_mp.cpp \
	client_mp/cl_parse_mp.cpp \
	client_mp/cl_scrn_mp.cpp \
	client_mp/cl_ui_mp.cpp \
	unknown/unknown_b013f8.cpp \
	qcommon/cm_load.cpp \
	qcommon/cm_load_obj.cpp \
	qcommon/cm_mesh.cpp \
	qcommon/cm_polylib.cpp \
	qcommon/cm_staticmodel.cpp \
	qcommon/cm_staticmodel_load_obj.cpp \
	qcommon/cm_test.cpp \
	qcommon/cm_trace.cpp \
	qcommon/cm_tracebox.cpp \
	qcommon/cm_world.cpp \
	qcommon/cmd.cpp \
	qcommon/com_bsp_load_obj.cpp \
	universal/com_file_wrapper.cpp \
	qcommon/unused_stubs.cpp \
	universal/com_files.cpp \
	universal/com_math.cpp \
	universal/com_memory.cpp \
	qcommon/com_playerprofile.cpp \
	qcommon/com_profilemapload.cpp \
	universal/com_shared.cpp \
	universal/com_sndalias.cpp \
	universal/com_sndalias_load_obj.cpp \
	qcommon/common.cpp \
	qcommon/legacyhacks.cpp \
	qcommon/mem_track.cpp \
	qcommon/dobj_management.cpp \
	universal/dvar.cpp \
	qcommon/dvar_cmds.cpp \
	universal/com_files_mp.cpp \
	qcommon/huffman.cpp \
	botlib/l_memory.cpp \
	botlib/l_precomp.cpp \
	botlib/l_script.cpp \
	qcommon/md4.cpp \
	universal/memfile.cpp \
	qcommon/msg_mp.cpp \
	qcommon/net_chan_mp.cpp \
	universal/q_parse.cpp \
	universal/q_shared.cpp \
	client_mp/screen_placement_mp.cpp \
	snd.cpp \
	snd_utils.cpp \
	qcommon/statmonitor.cpp \
	universal/surfaceflags.cpp \
	server_mp/sv_ccmds_mp.cpp \
	server_mp/sv_client_mp.cpp \
	server_mp/sv_game_mp.cpp \
	server_mp/sv_init_mp.cpp \
	server_mp/sv_main_mp.cpp \
	server_mp/sv_net_chan_mp.cpp \
	server_mp/sv_snapshot_mp.cpp \
	server_mp/sv_voice_mp.cpp \
	server_mp/sv_world_mp.cpp \
	win32/win_threads.cpp \
	ui/ui_component.cpp \
	win32/win_common.cpp \
	win32/win_configure.cpp \
	win32/win_input.cpp \
	win32/win_localize.cpp \
	win32/win_main.cpp \
	win32/win_net.cpp \
	win32/win_shared.cpp \
	win32/win_splash.cpp \
	win32/win_syscon.cpp \
	win32/win_wndproc.cpp \
	script/scr_animtree.cpp \
	script/scr_compiler.cpp \
	script/scr_debugger.cpp \
	script/scr_evaluate.cpp \
	script/scr_main.cpp \
	script/scr_memorytree.cpp \
	script/scr_parser.cpp \
	script/scr_parsetree.cpp \
	script/scr_stringlist.cpp \
	script/scr_tempmemory.cpp \
	stringed/loc_dvars.cpp \
	universal/dedicated_dvar.cpp \
	unknown/after_assertive.cpp \
	unknown/after_bg_weapons_load_obj.cpp \
	unknown/after_cm_polylib.cpp \
	unknown/after_com_memory.cpp \
	unknown/after_com_sndalias_load_obj.cpp \
	unknown/after_dobj_management.cpp \
	unknown/after_g_load_utils.cpp \
	unknown/after_g_misc_mp.cpp \
	unknown/after_g_mover_mp.cpp \
	unknown/after_msg_mp.cpp \
	unknown/after_scr_compiler.cpp \
	unknown/after_scr_const_mp.cpp \
	unknown/after_scr_tempmemory.cpp \
	unknown/after_scr_vm.cpp \
	unknown/after_xmodel_utils.cpp \
	script/scr_variable.cpp \
	script/scr_vm.cpp \
	script/scr_yacc.c \
	xanim/dobj.cpp \
	xanim/xanim.cpp \
	xanim/xanim_load.cpp \
	xanim/xmodel.cpp \
	xanim/xmodel_load.cpp \
	xanim/xmodel_load_obj.cpp \
	gfx_d3d/r_xsurface_load_obj.cpp \
	xanim/xmodel_utils.cpp \
	EffectsCore/FxArchive.cpp \
	EffectsCore/FxChannel.cpp \
	EffectsCore/FxCurve.cpp \
	EffectsCore/FxCurve_load_obj.cpp \
	EffectsCore/fx_dvars.cpp \
	EffectsCore/Fxexport.cpp \
	EffectsCore/FxMemMgr.cpp \
	EffectsCore/FxPrimitives.cpp \
	EffectsCore/FxProfile.cpp \
	EffectsCore/FxScheduler.cpp \
	EffectsCore/FxScheduler_load_obj.cpp \
	EffectsCore/FxSystem.cpp \
	EffectsCore/FxTemplate.cpp \
	EffectsCore/FxUtil.cpp \
	EffectsCore/GenericParser2.cpp \
	zlib/adler32.c \
	zlib/compress.c \
	zlib/deflate.c \
	zlib/infblock.c \
	zlib/infcodes.c \
	zlib/inffast.c \
	zlib/inflate.c \
	zlib/inftrees.c \
	zlib/infutil.c \
	zlib/trees.c \
	zlib/uncompr.c \
	zlib/unzip.c \
	zlib/zutil.c \
	stringed/stringed_hooks.cpp \
	stringed/stringed_ingame.cpp \
	stringed/stringed_interface.cpp \
	win32/cinematics.cpp \
	client_mp/cl_main_pc_mp.cpp \
	client_mp/cl_ui_pc_mp.cpp \
	qcommon/dl_main.cpp \
	win32/snd_driver.cpp \
	server_mp/sv_main_pc_mp.cpp \
	win32/win_voice.cpp \
	alias.cpp \
	globals.cpp \
	compat/imports.cpp \
	groupvoice/mixer.cpp \
	groupvoice/decode.cpp \
	groupvoice/encode.cpp \
	groupvoice/play.cpp \
	groupvoice/play_dsound.cpp \
	groupvoice/record.cpp \
	groupvoice/record_dsound.cpp \
	punkbuster/pbcl.cpp \
	punkbuster/pbmd5.cpp \
	punkbuster/pbsv.cpp \
	cgame_mp/cg_rumble_mp.cpp \
	cgame_mp/cg_main_mp.cpp \
	cgame_mp/cg_devgui.cpp \
	devgui/devgui.cpp \
	devgui/devgui_input.cpp \
	devgui/devgui_util.cpp \
	cgame_mp/cg_consolecmds_mp.cpp \
	cgame_mp/cg_drawtools_mp.cpp \
	game/g_debug_mp.cpp \
	cgame_mp/cg_newDraw_mp.cpp \
	cgame_mp/cg_draw_mp.cpp \
	cgame_mp/cg_ents_mp.cpp \
	cgame_mp/cg_marks_mp.cpp \
	cgame_mp/cg_view_mp.cpp \
	cgame_mp/cg_animtree_mp.cpp \
	cgame_mp/cg_servercmds_mp.cpp \
	cgame_mp/cg_shellshock.cpp \
	cgame_mp/cg_info_mp.cpp \
	cgame_mp/cg_weapons.cpp \
	cgame_mp/offhandweapons_mp.cpp \
	cgame/cg_effects_load_obj.cpp \
	cgame_mp/cg_localents_mp.cpp \
	cgame_mp/cg_scoreboard_mp.cpp \
	cgame_mp/cg_compassfriendlies_mp.cpp \
	cgame_mp/cg_players_mp.cpp \
	cgame_mp/cg_hudelem_mp.cpp \
	cgame_mp/cg_predict_mp.cpp \
	cgame_mp/cg_snapshot_mp.cpp \
	client_mp/cl_gamepad.cpp \
	cgame_mp/cg_playerstate_mp.cpp \
	cgame_mp/cg_event_mp.cpp \
	speex/gain_table.c \
	speex/exc_5_64_table.c \
	speex/hexc_table.c \
	speex/gain_table_lbr.c \
	speex/exc_5_256_table.c \
	speex/exc_8_128_table.c \
	speex/exc_20_32_table.c \
	speex/hexc_10_32_table.c \
	speex/exc_10_16_table.c \
	speex/exc_10_32_table.c \
	speex/lbr_48k_tables.c \
	speex/speex.c \
	speex/bits.c \
	speex/modes.c \
	speex/misc.c \
	speex/quant_lsp.c \
	speex/sb_celp.c \
	speex/nb_celp.c \
	speex/cb_search.c \
	speex/vbr.c \
	speex/lsp_tables_nb.c \
	speex/high_lsp_tables.c \
	speex/ltp.c \
	speex/lsp.c \
	speex/filters.c \
	speex/lpc.c \
	speex/vq.c \
	speex/speex_callbacks.c \
	bgame/bg_weapons.cpp \
	bgame/bg_animation_mp.cpp \
	game_mp/g_main_mp.cpp \
	game_mp/g_client_mp.cpp \
	game_mp/g_active_mp.cpp \
	game_mp/g_cmds_mp.cpp \
	game_mp/g_scr_main_mp.cpp \
	game_mp/g_svcmds_mp.cpp \
	game_mp/g_utils_mp.cpp \
	game_mp/g_spawn_mp.cpp \
	bgame/bg_mantle.cpp \
	game_mp/scr_const_mp.cpp \
	bgame/bg_misc.cpp \
	bgame/bg_misctables.cpp \
	bgame/bg_pmove.cpp \
	bgame/bg_weapons_load_obj.cpp \
	game_mp/g_misc_mp.cpp \
	game_mp/g_items_mp.cpp \
	game_mp/g_team_mp.cpp \
	game_mp/g_missile_mp.cpp \
	game_mp/g_combat_mp.cpp \
	game_mp/g_trigger_mp.cpp \
	game_mp/g_mover_mp.cpp \
	game_mp/g_hudelem_mp.cpp \
	game_mp/g_weapon_mp.cpp \
	game_mp/g_scr_mover_mp.cpp \
	game_mp/g_client_script_cmd_mp.cpp \
	game_mp/player_use_mp.cpp \
	game/g_load_utils.cpp \
	game_mp/g_client_fields_mp.cpp \
	bgame/bg_jump.cpp \
	bgame/bg_slidemove.cpp \
	game/g_weapon_load_obj.cpp \
	ui_mp/ui_main_mp.cpp \
	ui_mp/ui_shared_mp.cpp \
	ui/ui_shared_obj.cpp \
	ui_mp/ui_atoms.cpp \
	ui/ui_utils.cpp \
	ui_mp/ui_console_mode.cpp \
	ui_mp/ui_gameinfo_mp.cpp \
	ui_mp/ui_gamepad_menu.cpp \
	win32/gfx_dll_v60.cpp \
	win32/gfx_v60_threads.cpp \
	unknown/empty_2.cpp \
	unknown/empty_3.cpp \
	unknown/empty_4.cpp \
	unknown/empty_5.cpp \
	unknown/empty_6.cpp \
	libwww/Library/src/HTReqMan.c \
	libwww/Library/src/HTFTP.c \
	libwww/Library/src/HTAABrow.c \
	libwww/Library/src/HTInit.c \
	libwww/Library/src/HTTrace.c \
	libwww/Library/src/HTEvtLst.c \
	libwww/Library/src/HTProfil.c \
	libwww/Library/src/HTAccess.c \
	libwww/Library/src/HTMemory.c \
	libwww/Library/src/HTAlert.c \
	libwww/Library/src/HTParse.c \
	libwww/Library/src/HTNet.c \
	libwww/Library/src/HTHost.c \
	libwww/Library/src/HTString.c \
	libwww/Library/src/HTEscape.c \
	libwww/Library/src/HTAtom.c \
	libwww/Library/src/HTLib.c \
	libwww/Library/src/HTResponse.c \
	libwww/Library/src/HTError.c \
	libwww/Library/src/HTList.c \
	libwww/Library/src/HTAssoc.c \
	libwww/Library/src/HTAnchor.c \
	libwww/Library/src/HTNoFree.c \
	libwww/Library/src/HTEvent.c \
	libwww/Library/src/HTFormat.c \
	libwww/Library/src/HTChannl.c \
	libwww/Library/src/HTChunk.c \
	libwww/Library/src/HTUser.c \
	libwww/Library/src/HTTCP.c \
	libwww/Library/src/HTFTPDir.c \
	libwww/Library/src/HTBind.c \
	libwww/Library/src/HTUU.c \
	libwww/Library/src/HTAAUtil.c \
	libwww/Library/src/HTWWWStr.c \
	libwww/Library/src/HTDigest.c \
	libwww/Library/src/HTMethod.c \
	libwww/Library/src/HTRules.c \
	libwww/Library/src/HTCache.c \
	libwww/Library/src/HTGuess.c \
	libwww/Library/src/HTNewsLs.c \
	libwww/Library/src/HTTP.c \
	libwww/Library/src/HTMLGen.c \
	libwww/Library/src/HTBound.c \
	libwww/Library/src/HTMIME.c \
	libwww/Library/src/HTFSave.c \
	libwww/Library/src/HTTChunk.c \
	libwww/Library/src/HTFilter.c \
	libwww/Library/src/HTPEP.c \
	libwww/Library/src/HTHeader.c \
	libwww/Library/src/HTDialog.c \
	libwww/Library/src/HTANSI.c \
	libwww/Library/src/HTBufWrt.c \
	libwww/Library/src/HTTrans.c \
	libwww/Library/src/HTReader.c \
	libwww/Library/src/HTWriter.c \
	libwww/Library/src/HTTelnet.c \
	libwww/Library/src/HTFile.c \
	libwww/Library/src/HTGopher.c \
	libwww/Library/src/HTNews.c \
	libwww/Library/src/HTProt.c \
	libwww/Library/src/HTHome.c \
	libwww/Library/src/HTIcons.c \
	libwww/Library/src/HTMIMImp.c \
	libwww/Library/src/HTTimer.c \
	libwww/Library/src/HTInet.c \
	libwww/Library/src/HTBInit.c \
	libwww/Library/src/HTHInit.c \
	libwww/Library/src/HTProxy.c \
	libwww/Library/src/HTFWrite.c \
	libwww/Library/src/HTSChunk.c \
	libwww/Library/src/HTLink.c \
	libwww/Library/src/HTUTree.c \
	libwww/Library/src/HTDNS.c \
	libwww/Library/src/HTArray.c \
	libwww/Library/src/HTStream.c \
	libwww/Library/src/HTDir.c \
	libwww/Library/src/md5.c \
	libwww/Library/src/HTLocal.c \
	libwww/Library/src/HTNDir.c \
	libwww/Library/src/HTMIMERq.c \
	libwww/Library/src/HTTPReq.c \
	libwww/Library/src/HTMLPDTD.c \
	libwww/Library/src/HTMerge.c \
	libwww/Library/src/HTTee.c \
	libwww/Library/src/HTMIMPrs.c \
	libwww/Library/src/HTConLen.c \
	libwww/Library/src/HTLog.c \
	libwww/Library/src/HTMulti.c \
	libwww/Library/src/HTNewsRq.c \
	libwww/Library/src/HTTeXGen.c \
	libwww/Library/src/HTML.c \
	libwww/Library/src/HTPlain.c \
	libwww/Library/src/HTTPGen.c \
	libwww/Library/src/SGML.c \
	libwww/Library/src/HText.c
# files still compiled against the headers recovered from the Mac 1.3 build (oc/), with OCFLAGS
OCSRCS := \
	client_mp/cl_cgame_mp.cpp \
	client_mp/cl_cin_mp.cpp \
	client_mp/cl_console_mp.cpp \
	client_mp/cl_input.cpp \
	client_mp/cl_keys_mp.cpp \
	client_mp/cl_main_mp.cpp \
	client_mp/cl_devgui.cpp \
	client_mp/cl_net_chan_mp.cpp \
	client_mp/cl_parse_mp.cpp \
	client_mp/cl_scrn_mp.cpp \
	client_mp/cl_ui_mp.cpp \
	client_mp/screen_placement_mp.cpp \
	snd.cpp \
	snd_utils.cpp \
	qcommon/statmonitor.cpp \
	win32/win_threads.cpp \
	ui/ui_component.cpp \
	win32/win_localize.cpp \
	win32/win_syscon.cpp \
	win32/cinematics.cpp \
	client_mp/cl_main_pc_mp.cpp \
	client_mp/cl_ui_pc_mp.cpp \
	win32/snd_driver.cpp \
	win32/win_voice.cpp \
	alias.cpp \
	globals.cpp \
	groupvoice/mixer.cpp \
	groupvoice/decode.cpp \
	groupvoice/encode.cpp \
	groupvoice/play.cpp \
	groupvoice/record.cpp \
	cgame_mp/cg_rumble_mp.cpp \
	cgame_mp/cg_main_mp.cpp \
	cgame_mp/cg_devgui.cpp \
	cgame_mp/cg_consolecmds_mp.cpp \
	cgame_mp/cg_drawtools_mp.cpp \
	cgame_mp/cg_newDraw_mp.cpp \
	cgame_mp/cg_draw_mp.cpp \
	cgame_mp/cg_ents_mp.cpp \
	cgame_mp/cg_marks_mp.cpp \
	cgame_mp/cg_view_mp.cpp \
	cgame_mp/cg_animtree_mp.cpp \
	cgame_mp/cg_servercmds_mp.cpp \
	cgame_mp/cg_shellshock.cpp \
	cgame_mp/cg_info_mp.cpp \
	cgame_mp/cg_weapons.cpp \
	cgame_mp/offhandweapons_mp.cpp \
	cgame_mp/cg_localents_mp.cpp \
	cgame_mp/cg_scoreboard_mp.cpp \
	cgame_mp/cg_compassfriendlies_mp.cpp \
	cgame_mp/cg_players_mp.cpp \
	cgame_mp/cg_hudelem_mp.cpp \
	cgame_mp/cg_predict_mp.cpp \
	cgame_mp/cg_snapshot_mp.cpp \
	client_mp/cl_gamepad.cpp \
	cgame_mp/cg_playerstate_mp.cpp \
	cgame_mp/cg_event_mp.cpp \
	ui_mp/ui_main_mp.cpp \
	ui_mp/ui_shared_mp.cpp \
	ui/ui_shared_obj.cpp \
	ui_mp/ui_atoms.cpp \
	ui/ui_utils.cpp \
	ui_mp/ui_console_mode.cpp \
	ui_mp/ui_gameinfo_mp.cpp \
	ui_mp/ui_gamepad_menu.cpp \
	win32/gfx_dll_v60.cpp \
	win32/gfx_v60_threads.cpp
OBJS   := $(patsubst %,build/obj/%.obj,$(basename $(SRCS)))
LWOBJS := $(filter build/obj/libwww/%,$(OBJS))
EXEOBJS := $(filter-out build/obj/libwww/%,$(OBJS))
# extra cl flags for single files
build/obj/qcommon/dl_main.obj: TUFLAGS := /I.\\libwww\\Library\\src /D_WINDOWS
build/obj/cgame_mp/cg_localents_mp.obj: TUFLAGS := /DCOD2_NO_XCU_DECL
build/obj/speex/misc.obj: TUFLAGS := /TP
build/obj/libwww/Library/src/HTCache.obj: TUFLAGS := /Op

CL     := wine /opt/msvc710/Vc7/bin/cl.exe
LINK   := wine /opt/msvc710/Vc7/bin/link.exe
RC     := wine /opt/msvc710/Vc7/bin/rc.exe
CFLAGS := /nologo /c /O2 /GL /MT /DNDEBUG /DWIN32 /FI.\\compat\\msvc71.h /I.\\compat\\include \
	/I.\\universal /I. /I.\\qcommon /I.\\game /I.\\server_mp /I.\\bgame /I.\\script /I.\\xanim \
	/I.\\stringed /I.\\speex /I.\\speex\\speex
# files still compiled against the headers recovered from the Mac 1.3 build (oc/)
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
	@cd src && $(CL) $(if $(filter $*.cpp,$(OCSRCS)),$(OCFLAGS),$(CFLAGS)) $(TUFLAGS) /showIncludes /Fo..\\$(call win,$@) .\\$(call win,$*.cpp) > ../$@.log 2>&1 || (grep -v including ../$@.log; false)
	@$(deps)

build/obj/%.obj: src/%.c
	@mkdir -p $(dir $@)
	@cd src && $(CL) $(CFLAGS) $(TUFLAGS) /showIncludes /Fo..\\$(call win,$@) .\\$(call win,$*.c) > ../$@.log 2>&1 || (grep -v including ../$@.log; false)
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
		'$(subst /,\,$(CLDOS)) $(WFLAGS) $(TUFLAGS) /showIncludes /Fo$(subst /,\,Z:/w/$@) \builds\pc_1.3_1_1\pc\cod2src\$(subst /,\,libwww/$*.c)' \
		> $@.bat
	@$(WCL) '$(subst /,\,Z:/w/$@.bat)' > $@.log 2>&1 || (grep -v including $@.log; rm -f $@; false)
LIBS   := winmm.lib wsock32.lib $(call win,$(IMPLIBS)) dsound.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib $(call win,build/lib/libwww.lib) libcmt.lib

# retail links libwww as an archive after the import libs: its members land after the import thunks, before libcmt
build/lib/libwww.lib: $(LWOBJS)
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

$(OUT): $(EXEOBJS) build/lib/libwww.lib $(IMPLIBS) build/cod2mp.res
	@printf '%s\n' $(call win,$(EXEOBJS)) > build/objs.rsp
	$(LINK) $(LFLAGS) /OUT:$(call win,$@) @build\\objs.rsp build\\cod2mp.res $(LIBS) > build/link.log 2>&1; tail -1 build/link.log

$(REL): $(EXEOBJS) build/lib/libwww.lib $(IMPLIBS) build/cod2mp.res Makefile
	@mkdir -p $(dir $@)
	@mkdir -p "$$(winepath -u 'c:\builds\pc_1.3_1_1\pc\cod2\pc')"
	@printf '%s\n' $(call win,$(EXEOBJS)) > build/objs.rsp
	wineserver -k 2>/dev/null; export FAKETIME='2006-05-02 00:09:51' GUIDPIN=$(PDB_GUID) LD_PRELOAD="$(wildcard /usr/lib/*/faketime/libfaketime.so.1) $(CURDIR)/build/guidpin.so"; $(LINK) $(subst /FIXED:NO,/FIXED,$(subst build\\CoD2MP_s.map,build\\release\\CoD2MP_s.map,$(LFLAGS))) /DEBUG '/PDB:c:\builds\pc_1.3_1_1\pc\cod2\pc\CoD2MP_s.pdb' /OUT:$(call win,$@) @build\\objs.rsp build\\cod2mp.res $(LIBS) > build/release/link.log 2>&1 || { tail -10 build/release/link.log; exit 1; }
	@! grep -E 'LNK2001|LNK2019|fatal error' build/release/link.log
	@true # 1.0-only mixerGetRecordLevel postlink is disabled for 1.3
	@cp "$$(winepath -u 'c:\builds\pc_1.3_1_1\pc\cod2\pc\CoD2MP_s.pdb')" build/release/CoD2MP_s.pdb

endif
