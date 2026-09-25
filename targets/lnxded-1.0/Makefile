# Linux dedicated server 1.0 (cod2_lnxded_1_0a).
#   make                  build build/cod2_lnxded_1_0a in the toolchain image
#   make check            compare its SHA-256 with checksums.yml
#   make verify           compare every TU with your original binary (host: python3, binutils)
#   make build/obj/<dir>/<file>.o    build one TU
#   make clean

IMAGE  ?= cod2engine-linux-2005
ANCHOR ?= ../../binaries/linux/cod2_lnxded_1_0a
OUT    := build/cod2_lnxded_1_0a

ifndef IN_IMAGE

DOCKER := docker run --rm --platform linux/386 -u $$(id -u):$$(id -g) -v "$(CURDIR)":/work -w /work $(IMAGE)

all:
	$(DOCKER) make -j$$(nproc) IN_IMAGE=1 $(OUT)

build/obj/%.o: FORCE
	$(DOCKER) make IN_IMAGE=1 $@

check: all
	@test "$$(sha256sum < $(OUT) | cut -c1-64)" = "$$(awk '/sha256:/ {print $$2}' checksums.yml)" \
		&& echo "SHA256 IDENTICAL" || { echo "SHA256 DIFFERS"; exit 1; }

verify: all
	ANCHOR="$(abspath $(ANCHOR))" sh tools/verify.sh

clean:
	rm -rf build

.PHONY: all check verify clean FORCE

else

# Inside the toolchain image.
CRT  := /opt/crt-2005
LD   := /opt/binutils-2.14.90.0.6/bin/ld
PRE  := libdl.so.2 libpthread.so.0
POST := libstdc++.so.5 libm.so.6 libgcc_s.so.1 libc.so.6

TUS  := $(shell grep -v '^\#' src/tus.txt | awk '{ print $$1 }')
OBJS := $(patsubst %,build/obj/%.o,$(basename $(TUS)))

# --traditional-format: the FDEs use unrelaxed DW_CFA_advance_loc4.
# sysroot_nothrow: the libc declarations as the original build saw them.
CFLAGS := -w -m32 -O0 -fno-pic -DNDEBUG -DNOUNCRYPT -falign-functions=2 -Wa,--traditional-format
INC    := -include src/compat/gcc334_compat.h -I/work/src/compat/sysroot_nothrow \
	-Isrc/universal -Isrc -Isrc/qcommon -Isrc/game -Isrc/server -Isrc/bgame \
	-Isrc/script -Isrc/xanim -Isrc/stringed -Isrc/unix

# Extra flags per TU: the columns after the address in src/tus.txt.
tuflags = $(shell awk '$$1 == "$(1)" { $$1 = $$2 = ""; print }' src/tus.txt)

build/obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	g++ $(CFLAGS) $(call tuflags,$*.cpp) $(INC) -MMD -MP -c $< -o $@

build/obj/%.o: src/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $(call tuflags,$*.c) $(INC) -MMD -MP -c $< -o $@

# Stand-ins for the shared libraries: the original's imports, nothing more.
build/lib/%: imports/%.S imports/%.map
	@mkdir -p $(@D)
	gcc -m32 -shared -nostdlib -Wl,-soname,$* -Wl,--version-script,imports/$*.map -o $@ $<

# The original link command was g++ -ldl -lpthread <objects>.
$(OUT): $(OBJS) $(addprefix build/lib/,$(PRE) $(POST))
	$(LD) -m elf_i386 -s -dynamic-linker /lib/ld-linux.so.2 -Map build/link.map -o $@ \
		$(CRT)/crt1.o $(CRT)/crti.o $(CRT)/crtbegin.o $(addprefix build/lib/,$(PRE)) \
		$(OBJS) $(addprefix build/lib/,$(POST)) $(CRT)/crtend.o $(CRT)/crtn.o

-include $(OBJS:.o=.d)

endif
