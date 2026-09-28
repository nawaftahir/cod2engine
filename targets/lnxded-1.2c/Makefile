# Linux dedicated server 1.2c (cod2_lnxded_1_2c).
#   make                  build build/cod2_lnxded_1_2c in the toolchain image
#   make check            compare its SHA-256 with checksums.yml
#   make verify           compare every TU with your original binary (host: python3, binutils)
#   make build/obj/<dir>/<file>.o    build one TU
#   make clean
#
# src/ holds only what differs from 1.0; every other source and header comes from
# ../lnxded-1.0/src (BASE).

IMAGE  ?= cod2engine-linux-breezy
ANCHOR ?= ../../binaries/linux/cod2_lnxded_1_2c
OUT    := build/cod2_lnxded_1_2c
BASE   := ../lnxded-1.0/src

ifndef IN_IMAGE

REPO   := $(abspath ../..)
DOCKER := docker run --rm --platform linux/386 -u $$(id -u):$$(id -g) -v "$(REPO)":/repo \
	-w /repo/targets/$(notdir $(CURDIR)) $(IMAGE)

all:
	$(DOCKER) make -j$$(nproc) IN_IMAGE=1 $(OUT)

build/obj/%.o: FORCE
	$(DOCKER) make IN_IMAGE=1 $@

check: all
	@test "$$(sha256sum < $(OUT) | cut -c1-64)" = "$$(awk '/sha256:/ {print $$2}' checksums.yml)" \
		&& echo "SHA256 IDENTICAL" || { echo "SHA256 DIFFERS"; exit 1; }

objs:
	$(DOCKER) make -k -j$$(nproc) IN_IMAGE=1 objs

verify: objs
	ANCHOR="$(abspath $(ANCHOR))" sh tools/verify.sh

clean:
	rm -rf build

.PHONY: all check objs verify clean FORCE

else

# Inside the toolchain image.
CC   := gcc-3.3
CXX  := g++-3.3

TUS  := $(shell grep -v '^\#' src/tus.txt | awk '{ print $$1 }')
OBJS := $(patsubst %,build/obj/%.o,$(basename $(TUS)))

# No --traditional-format: 1.2c's FDEs use relaxed DW_CFA_advance_loc.
CFLAGS := -w -m32 -O0 -fno-pic -DNDEBUG -DNOUNCRYPT -falign-functions=2
# -I-: quote includes skip the including file's own directory, so a header copied into
# src/ overrides the base one for every TU. No header basename occurs twice.
DIRS   := universal . qcommon game server bgame script xanim stringed unix botlib EffectsCore \
	cgame client unknown zlib punkbuster
INC    := -include $(BASE)/compat/gcc334_compat.h -I- \
	$(foreach d,$(DIRS),-Isrc/$(d) -I$(BASE)/$(d))
# "../x/y.h" resolves through src/<dir> only when that directory exists
$(shell mkdir -p $(addprefix src/,$(DIRS)))

vpath %.c   src $(BASE)
vpath %.cpp src $(BASE)

tuflags = $(shell awk '$$1 == "$(1)" { $$1 = $$2 = ""; print }' src/tus.txt)

build/obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(call tuflags,$*.cpp) $(INC) -MMD -MP -c $< -o $@

build/obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(call tuflags,$*.c) $(INC) -MMD -MP -c $< -o $@

objs: $(OBJS)

# Link as the g++-3.3 driver does (.comment order: crt1 crti crtbegin, game, libc_nonshared,
# crtend crtn), against stub libraries that export exactly the anchor's imports.
GCCLIB := /usr/lib/gcc-lib/i486-linux-gnu/3.3.6
STRIP  ?= -s
PRE    := libdl.so.2 libpthread.so.0
POST   := libstdc++.so.5 libm.so.6 libgcc_s.so.1 libc.so.6

build/lib/%: imports/%.S imports/%.map
	@mkdir -p $(@D)
	$(CC) -m32 -shared -nostdlib -Wl,-soname,$* -Wl,--version-script,imports/$*.map -o $@ $<

$(OUT): $(OBJS) $(addprefix build/lib/,$(PRE) $(POST))
	ld --eh-frame-hdr -m elf_i386 $(STRIP) -dynamic-linker /lib/ld-linux.so.2 -Map build/link.map -o $@ \
		/usr/lib/crt1.o /usr/lib/crti.o $(GCCLIB)/crtbegin.o $(addprefix build/lib/,$(PRE)) \
		$(OBJS) $(addprefix build/lib/,$(POST)) /usr/lib/libc_nonshared.a \
		$(GCCLIB)/crtend.o /usr/lib/crtn.o

-include $(OBJS:.o=.d)

endif
