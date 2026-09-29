# Linux dedicated server 1.0 (cod2_lnxded_1_0a).
#   make          build build/cod2_lnxded_1_0a inside the toolchain image
#   make check    compare its SHA-256 with checksums.yml
#   make verify   compare every TU with the original (host python3 + binutils)
#   make toolchain  build the toolchain image
#   make clean

IMAGE := cod2engine-linux-2005
OUT   := build/cod2_lnxded_1_0a

ifndef IN_IMAGE

DOCKER := docker run --rm --platform linux/386 -u $$(id -u):$$(id -g) -v "$(CURDIR)":/work -w /work $(IMAGE)

all:
	$(DOCKER) make -j$$(nproc) IN_IMAGE=1 $(OUT)

check: all
	@test "$$(sha256sum < $(OUT) | cut -c1-64)" = "$$(awk '/sha256:/ {print $$2}' checksums.yml)" \
		&& echo "SHA256 IDENTICAL" || { echo "SHA256 DIFFERS"; exit 1; }

verify: all
	tools/verify.sh

toolchain:
	docker build --platform linux/386 -t $(IMAGE) ../toolchains/linux-2005

clean:
	rm -rf build

.PHONY: all check verify toolchain clean

else

# Link order: it decides where every function and variable lands in the binary.
SRCS := \
	botlib/l_memory.cpp \
	botlib/l_precomp.cpp \
	botlib/l_script.cpp \
	qcommon/buildnumber.c \
	qcommon/com_bsp_load_obj.cpp \
	qcommon/cm_load.cpp \
	qcommon/cm_load_obj.cpp \
	qcommon/cm_mesh.cpp \
	qcommon/cm_polylib.cpp \
	unknown/after_cm_polylib.cpp \
	qcommon/cm_staticmodel.cpp \
	qcommon/cm_staticmodel_load_obj.cpp \
	qcommon/cm_test.cpp \
	qcommon/cm_trace.cpp \
	qcommon/cm_tracebox.cpp \
	qcommon/cm_world.cpp \
	qcommon/cmd.cpp \
	universal/com_file_wrapper.cpp \
	universal/com_memory_high.cpp \
	qcommon/common.cpp \
	qcommon/dobj_management.cpp \
	unknown/after_dobj_management.cpp \
	universal/dvar_cmds.cpp \
	universal/com_files_mp.cpp \
	qcommon/huffman.cpp \
	qcommon/unused_stubs.cpp \
	qcommon/md4.cpp \
	qcommon/msg_mp.cpp \
	unknown/after_msg_mp.cpp \
	qcommon/net_chan_mp.cpp \
	qcommon/unused_buffer.cpp \
	script/scr_animtree.cpp \
	script/scr_compiler.cpp \
	unknown/after_scr_compiler.cpp \
	script/scr_main.cpp \
	script/scr_memorytree.cpp \
	script/scr_parser.cpp \
	script/scr_stringlist.cpp \
	script/scr_tempmemory.cpp \
	unknown/after_scr_tempmemory.cpp \
	script/scr_variable.cpp \
	script/scr_vm.cpp \
	unknown/after_scr_vm.cpp \
	script/scr_yacc.c \
	server/sv_ccmds_mp.cpp \
	server/sv_client_mp.cpp \
	server/sv_game_mp.cpp \
	server/sv_init_mp.cpp \
	server/sv_main_mp.cpp \
	server/sv_main_pc_mp.cpp \
	server/sv_net_chan_mp.cpp \
	server/sv_snapshot_mp.cpp \
	server/sv_voice_mp.cpp \
	server/sv_world_mp.cpp \
	universal/assertive.cpp \
	unknown/after_assertive.cpp \
	universal/com_files.cpp \
	universal/dedicated_dvar.cpp \
	universal/com_math.cpp \
	universal/com_memory.cpp \
	unknown/after_com_memory.cpp \
	universal/com_shared.cpp \
	universal/com_sndalias.cpp \
	universal/com_sndalias_load_obj.cpp \
	unknown/after_com_sndalias_load_obj.cpp \
	universal/dvar.cpp \
	stringed/loc_dvars.cpp \
	universal/memfile.cpp \
	universal/q_parse.cpp \
	universal/q_shared.cpp \
	universal/surfaceflags.cpp \
	xanim/dobj.cpp \
	xanim/xanim.cpp \
	xanim/xanim_load.cpp \
	xanim/xmodel.cpp \
	xanim/xmodel_load.cpp \
	xanim/xmodel_utils.cpp \
	unknown/after_xmodel_utils.cpp \
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
	unix/unix_dir.c \
	unix/unix_main.cpp \
	unix/unix_net.cpp \
	unix/unix_shared.cpp \
	unix/unix_threads.cpp \
	client/snd_null.cpp \
	unknown/after_snd_null.cpp \
	bgame/bg_animation_mp.cpp \
	bgame/bg_jump.cpp \
	bgame/bg_mantle.cpp \
	bgame/bg_misc.cpp \
	bgame/bg_misctables.cpp \
	bgame/bg_pmove.cpp \
	bgame/bg_slidemove.cpp \
	bgame/bg_weapons.cpp \
	bgame/bg_weapons_load_obj.cpp \
	unknown/after_bg_weapons_load_obj.cpp \
	cgame/cg_predict_mp.cpp \
	game/g_load_utils.cpp \
	unknown/after_g_load_utils.cpp \
	game/g_weapon_load_obj.cpp \
	game/g_active_mp.cpp \
	game/g_client_fields_mp.cpp \
	game/g_client_mp.cpp \
	game/g_client_script_cmd_mp.cpp \
	game/g_cmds_mp.cpp \
	game/g_combat_mp.cpp \
	game/g_debug_mp.cpp \
	game/g_hudelem_mp.cpp \
	game/g_items_mp.cpp \
	game/g_main_mp.cpp \
	game/g_misc_mp.cpp \
	unknown/after_g_misc_mp.cpp \
	game/g_missile_mp.cpp \
	game/g_mover_mp.cpp \
	unknown/after_g_mover_mp.cpp \
	game/g_scr_main_mp.cpp \
	game/g_scr_mover_mp.cpp \
	game/g_spawn_mp.cpp \
	game/g_svcmds_mp.cpp \
	game/g_team_mp.cpp \
	game/g_trigger_mp.cpp \
	game/g_utils_mp.cpp \
	game/g_weapon_mp.cpp \
	game/player_use_mp.cpp \
	game/scr_const_mp.cpp \
	unknown/after_scr_const_mp.cpp \
	EffectsCore/FxArchive.cpp \
	EffectsCore/FxChannel.cpp \
	EffectsCore/FxCurve.cpp \
	EffectsCore/FxCurve_load_obj.cpp \
	EffectsCore/FxMemMgr.cpp \
	EffectsCore/FxPrimitives.cpp \
	EffectsCore/FxScheduler.cpp \
	EffectsCore/FxScheduler_load_obj.cpp \
	EffectsCore/FxSystem.cpp \
	EffectsCore/FxTemplate.cpp \
	EffectsCore/Fxexport.cpp \
	EffectsCore/GenericParser2.cpp \
	EffectsCore/fx_dvars.cpp \
	EffectsCore/FxUtil.cpp \
	stringed/stringed_hooks.cpp \
	stringed/stringed_interface.cpp \
	stringed/stringed_ingame.cpp

OBJS := $(patsubst %,build/obj/%.o,$(basename $(SRCS)))

# --traditional-format: the FDEs use unrelaxed DW_CFA_advance_loc4.
# sysroot_nothrow: the libc declarations as the original build saw them.
CFLAGS := -w -m32 -O0 -fno-pic -DNDEBUG -DNOUNCRYPT -falign-functions=2 -Wa,--traditional-format \
	-include src/compat/gcc334_compat.h -I/work/src/compat/sysroot_nothrow \
	-Isrc/universal -Isrc -Isrc/qcommon -Isrc/game -Isrc/server -Isrc/bgame \
	-Isrc/script -Isrc/xanim -Isrc/stringed -Isrc/unix

build/obj/script/scr_yacc.o: TUFLAGS := -falign-functions=1
build/obj/zlib/adler32.o: TUFLAGS := -falign-functions=1
build/obj/zlib/compress.o: TUFLAGS := -falign-functions=1
build/obj/zlib/deflate.o: TUFLAGS := -falign-functions=1
build/obj/zlib/infblock.o: TUFLAGS := -falign-functions=1
build/obj/zlib/infcodes.o: TUFLAGS := -falign-functions=1
build/obj/zlib/inffast.o: TUFLAGS := -falign-functions=1
build/obj/zlib/inflate.o: TUFLAGS := -falign-functions=1
build/obj/zlib/inftrees.o: TUFLAGS := -falign-functions=1
build/obj/zlib/infutil.o: TUFLAGS := -falign-functions=1
build/obj/zlib/trees.o: TUFLAGS := -falign-functions=1
build/obj/zlib/uncompr.o: TUFLAGS := -falign-functions=1
build/obj/zlib/unzip.o: TUFLAGS := -falign-functions=1
build/obj/zlib/zutil.o: TUFLAGS := -falign-functions=1
build/obj/EffectsCore/FxCurve.o: TUFLAGS := -fno-exceptions
build/obj/stringed/stringed_interface.o: TUFLAGS := -I/usr/include/c++/3.3 -I/usr/include/c++/3.3/i486-linux
build/obj/stringed/stringed_ingame.o: TUFLAGS := -I/usr/include/c++/3.3 -I/usr/include/c++/3.3/i486-linux

build/obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	g++ $(CFLAGS) $(TUFLAGS) -MMD -MP -c $< -o $@

build/obj/%.o: src/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $(TUFLAGS) -MMD -MP -c $< -o $@

# Stand-ins for the shared libraries: the original's imports, nothing more.
CRT  := /opt/crt-2005
LD   := /opt/binutils-2.14.90.0.6/bin/ld
PRE  := libdl.so.2 libpthread.so.0
POST := libstdc++.so.5 libm.so.6 libgcc_s.so.1 libc.so.6

build/lib/%: imports/%.S imports/%.map
	@mkdir -p $(@D)
	gcc -m32 -shared -nostdlib -Wl,-soname,$* -Wl,--version-script,imports/$*.map -o $@ $<

# The original link command was g++ -ldl -lpthread <objects>.
$(OUT): $(OBJS) $(addprefix build/lib/,$(PRE) $(POST))
	$(LD) -m elf_i386 -s -Map build/link.map -dynamic-linker /lib/ld-linux.so.2 -o $@ \
		$(CRT)/crt1.o $(CRT)/crti.o $(CRT)/crtbegin.o $(addprefix build/lib/,$(PRE)) \
		$(OBJS) $(addprefix build/lib/,$(POST)) $(CRT)/crtend.o $(CRT)/crtn.o

-include $(OBJS:.o=.d)

endif
