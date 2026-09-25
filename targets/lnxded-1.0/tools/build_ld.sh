#!/bin/sh
# Build the linker the anchor was linked with: H.J. Lu's binutils 2.14.90.0.6
# (2003-08-20). The anchor has PT_GNU_STACK (mainline 2003-06-03) and keeps the
# PLT address of every imported function in .dynsym (zeroed from 2003-11-22).
# Output: build/binutils/o6/ld/ld-new (tools/link.sh uses it).
set -e
V=2.14.90.0.6
D=build/binutils
mkdir -p $D
[ -f $D/binutils-$V.tar.gz ] || curl -sfL -o $D/binutils-$V.tar.gz \
	https://mirrors.edge.kernel.org/pub/linux/devel/binutils/binutils-$V.tar.gz
echo "8757f67a0512ec1d55df55e35926be5faaa5ba3236f8f28b3f3dcdb613a41095  $D/binutils-$V.tar.gz" | sha256sum -c - >/dev/null
[ -d $D/binutils-$V ] || tar xzf $D/binutils-$V.tar.gz -C $D
# The snapshot ships no generated parser; any flex/bison produces an equivalent one.
[ -f $D/binutils-$V/ld/ldgram.c ] || docker run --rm -v "$PWD/$D/binutils-$V/ld":/w -w /w debian:trixie-slim sh -ec "
	apt-get -qq update && apt-get -qq install -y flex bison >/dev/null
	flex -oldlex.c ldlex.l && bison -y -d -o ldgram.c ldgram.y
	chown $(id -u):$(id -g) ldlex.c ldgram.c ldgram.h"
docker run --rm --platform linux/386 -u "$(id -u):$(id -g)" -v "$PWD/$D":/w -w /w ${TU_IMG:-cod2engine-gcc334} sh -ec "
	rm -rf o6 && mkdir o6 && cd o6
	export ac_cv_prog_LEX=flex ac_cv_prog_lex_root=lex.yy ac_cv_prog_lex_yytext_pointer=yes ac_cv_lib_fl_yywrap=yes
	../binutils-$V/configure --disable-nls --build=i686-pc-linux-gnu --host=i686-pc-linux-gnu --target=i686-pc-linux-gnu >/dev/null
	make -j8 all-ld >/dev/null
	./ld/ld-new --version | head -1"
