#!/bin/sh
# Compare every TU of a built target with the original. Run from the target directory
# after `make`; each object's .text address comes from build/link.map.
# Header inlines are link-once sections; rename them (.lo.*) so tu_verify can
# place each copy: after this TU's .text when it owns it, else at the owner's address.
T=$(dirname "$0")
D=build/verify
rm -rf $D && mkdir -p $D
# ".text  0xVA  0xSIZE  build/obj/x.o", the name wrapped onto its own line when long
awk '$1 == ".text" && NF == 1 {w = 1; next}
	w && $3 ~ /^build\/obj\// {print $3, $1} {w = 0}
	$1 == ".text" && $4 ~ /^build\/obj\// {print $4, $2}' build/link.map > $D/text.va
sed -n 's/^SRCS :=//; /^\t[^ ]*\.c/{s/^\t//; s/ .*//; p}' Makefile | while read -r src; do
	obj=build/obj/${src%.*}.o
	va=$(awk -v o="$obj" '$1 == o {print $2}' $D/text.va)
	o=$D/$(echo "${src%.*}" | tr / _).o
	lo=$(objdump -h "$obj" | awk '$2 ~ /^\.gnu\.linkonce\.t\./ {n=$2; sub(/^\.gnu\.linkonce\.t\./, "", n); printf " --rename-section %s=.lo.%s", $2, n}')
	objcopy $lo "$obj" "$o"
	KEEP="${o%.o}.elf" python3 "$T/tu_verify.py" "$o" "${va:--}" > "${o%.o}.verify"
	r=$(tail -1 "${o%.o}.verify")
	echo "$r  $src"
	[ "$r" = "TU VERIFIED" ] || touch $D/.fail
done
[ ! -e $D/.fail ]
