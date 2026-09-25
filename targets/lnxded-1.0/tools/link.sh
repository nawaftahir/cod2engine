#!/bin/sh
# Link every TU in src/tus.txt order into build/cod2_lnxded_1_0a against import
# stubs made from the anchor's own imports, then compare with the anchor.
# Run tools/tu_all.sh first (it builds build/tu/*.o).
# The linker: tools/build_ld.sh (override with LD=).
set -e
ANCHOR=${ANCHOR:-../../binaries/linux/cod2_lnxded_1_0a}
OUT=build/cod2_lnxded_1_0a
rm -rf build/link && mkdir -p build/link build/implib
# The g++ driver's order: startfiles, the user's arguments (-ldl -lpthread came
# before the objects: the anchor's .dynstr records dl* and pthread names at
# their first object reference), the driver's libraries, then crtend/crtn.
PRE="libdl.so.2 libpthread.so.0"
POST="libstdc++.so.5 libm.so.6 libgcc_s.so.1 libc.so.6"

# tu_build renames header inlines to .lo.* for tu_verify; the link needs them
# back as link-once sections so only the first copy in link order is kept.
objs=$(grep -v '^#' src/tus.txt | while read -r src va flags; do
	[ -n "$src" ] || continue
	b=$(basename "${src%.*}")
	[ "$b" = crtend ] && for so in $POST; do echo "build/implib/$so"; done
	lo=$(objdump -h "build/tu/$b.o" | awk '$2 ~ /^\.lo\./ {n=$2; sub(/^\.lo\./, "", n); printf " --rename-section %s=.gnu.linkonce.t.%s", $2, n}')
	objcopy $lo "build/tu/$b.o" "build/link/$b.o"
	echo "build/link/$b.o"
	[ "$b" = crtbegin ] && for so in $PRE; do echo "build/implib/$so"; done
done | tr '\n' ' ')

python3 tools/implib.py "$ANCHOR" build/implib >/dev/null
libs="$PRE $POST"

docker run --rm --platform linux/386 -u "$(id -u):$(id -g)" -v "$PWD":/work -w /work -e LD ${TU_IMG:-cod2engine-gcc334} sh -ec "
for so in $libs; do
	gcc -m32 -shared -nostdlib -Wl,-soname,\$so -Wl,--version-script,build/implib/\$so.map -o build/implib/\$so build/implib/\$so.S
done
${LD:-build/binutils/o6/ld/ld-new} -m elf_i386 -s -dynamic-linker /lib/ld-linux.so.2 -Map build/link.map -o $OUT $objs"

a=$(sha256sum < "$ANCHOR" | cut -c1-64); o=$(sha256sum < "$OUT" | cut -c1-64)
echo "anchor $a"; echo "linked $o"
[ "$a" = "$o" ] && echo "SHA256 IDENTICAL" || { echo "SHA256 DIFFERS"; exit 1; }
