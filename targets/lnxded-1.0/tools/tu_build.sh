#!/bin/sh
# Compile one translation unit: tools/tu_build.sh src/<dir>/<file>.cpp
# Output: build/tu/<file>.o
#   --traditional-format      the FDEs use unrelaxed DW_CFA_advance_loc4
#   src/compat/sysroot_nothrow  the libc declarations carried no throw()
set -e
src=$1; out=build/tu/$(basename "${src%.*}").o
case "$src" in *.c) CC=gcc;; *) CC=g++;; esac
INC="-Isrc/universal -Isrc -Isrc/qcommon -Isrc/game -Isrc/server -Isrc/bgame -Isrc/script -Isrc/xanim -Isrc/stringed -Isrc/unix"
mkdir -p build/tu
docker run --rm --platform linux/386 -u "$(id -u):$(id -g)" -v "$PWD":/work -w /work ${TU_IMG:-cod2engine-gcc334} \
  $CC -w -m32 -O0 -fno-pic -DNDEBUG -DNOUNCRYPT -falign-functions=2 -Wa,--traditional-format $TUFLAGS \
  -include src/compat/gcc334_compat.h -I/work/src/compat/sysroot_nothrow $INC -c "$src" -o "$out"
# header inlines land in .gnu.linkonce.t.*, and the final link keeps only the first
# copy in link order. Rename them (.lo.*) so tu_verify can place each one: after
# this TU's .text when this TU owns it, else at the owner's address.
lo=$(objdump -h "$out" | awk '$2 ~ /^\.gnu\.linkonce\.t\./ {n=$2; sub(/^\.gnu\.linkonce\.t\./, "", n); printf " --rename-section %s=.lo.%s", $2, n}')
[ -n "$lo" ] && objcopy $lo "$out"
echo "$out"
