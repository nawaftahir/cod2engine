#!/bin/sh
# Compare every TU in src/tus.txt with the original binary (run through `make verify`).
# Header inlines are link-once sections; rename them (.lo.*) so tu_verify can
# place each copy: after this TU's .text when it owns it, else at the owner's address.
D=build/verify
rm -rf $D && mkdir -p $D
grep -v '^#' src/tus.txt | while read -r src va flags; do
	[ -n "$src" ] || continue
	obj=build/obj/${src%.*}.o
	o=$D/$(basename "${src%.*}").o
	lo=$(objdump -h "$obj" | awk '$2 ~ /^\.gnu\.linkonce\.t\./ {n=$2; sub(/^\.gnu\.linkonce\.t\./, "", n); printf " --rename-section %s=.lo.%s", $2, n}')
	objcopy $lo "$obj" "$o"
	KEEP="${o%.o}.elf" python3 tools/tu_verify.py "$o" "$va" > "${o%.o}.verify"
	r=$(tail -1 "${o%.o}.verify")
	echo "$r  $src"
	[ "$r" = "TU VERIFIED" ] || touch $D/.fail
done
[ ! -e $D/.fail ]
