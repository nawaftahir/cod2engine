#!/bin/sh
# Build and verify every clean TU listed in src/tus.txt; exit 1 if any fails.
rm -f build/tu/*.syms.json build/tu/.fail
grep -v '^#' src/tus.txt | while read -r src va flags; do
	[ -n "$src" ] || continue
	o="build/tu/$(basename "${src%.*}")"
	TUFLAGS="$flags" sh tools/tu_build.sh "src/$src" >/dev/null || { echo "BUILD FAIL $src"; rm -f "$o.verify"; touch build/tu/.fail; continue; }
	[ "$va" = link ] && { echo "LINK ONLY  $src"; rm -f "$o.verify"; continue; }
	python3 tools/tu_verify.py "$o.o" "$va" > "$o.verify"
	r=$(tail -1 "$o.verify")
	echo "$r  $src"
	[ "$r" = "TU VERIFIED" ] || touch build/tu/.fail
done
[ ! -e build/tu/.fail ]
