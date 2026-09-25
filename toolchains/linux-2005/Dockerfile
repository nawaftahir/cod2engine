# The 2005 Linux build system, as far as the binaries record it:
#   gcc/g++ 3.3.4         /usr/local/bin/gcc, g++
#   binutils 2.14.90.0.6  /opt/binutils-2.14.90.0.6/bin/ld
#   startup objects       /opt/crt-2005/{crt1,crti,crtbegin,crtend,crtn}.o
#
#   docker build --platform linux/386 -t cod2engine-linux-2005 toolchains/linux-2005
#
# See README.md for the evidence behind each piece.

# Fetch and check the sources on a current system (sarge has no sha256sum or
# modern TLS), and generate the linker's parser (the snapshot ships none).
FROM debian:trixie-slim AS src
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates flex bison
WORKDIR /src
RUN curl -fsSLO https://ftpmirror.gnu.org/gcc/gcc-3.3.4/gcc-core-3.3.4.tar.gz \
 && curl -fsSLO https://ftpmirror.gnu.org/gcc/gcc-3.3.4/gcc-g++-3.3.4.tar.gz \
 && curl -fsSLO https://mirrors.edge.kernel.org/pub/linux/devel/binutils/binutils-2.14.90.0.6.tar.gz \
 && printf '%s  %s\n' \
    4cb79096cc37f45dcbac928db6e3c7f25dcea92f505bcdcda8dcc40105dd6759 gcc-core-3.3.4.tar.gz \
    976d3ee48f9c294fa35646222e4fb2260443b3083f6e9084bdb2631e5142ac5e gcc-g++-3.3.4.tar.gz \
    8757f67a0512ec1d55df55e35926be5faaa5ba3236f8f28b3f3dcdb613a41095 binutils-2.14.90.0.6.tar.gz \
    | sha256sum -c -
RUN tar xzf binutils-2.14.90.0.6.tar.gz && rm binutils-2.14.90.0.6.tar.gz \
 && cd binutils-2.14.90.0.6/ld \
 && flex -oldlex.c ldlex.l && bison -y -d -o ldgram.c ldgram.y

# Debian sarge provides the host tools, including GNU as 2.15.
FROM debian/eol:sarge
RUN apt-get update && apt-get install -y build-essential binutils make libncurses5-dev \
 && rm -rf /var/lib/apt/lists/*

# gcc is built without HAVE_AS_LEB128: the original .gcc_except_table uses
# udata4 call-site entries, which gcc 3.3 emits only when configure found an
# assembler without .uleb128 support.
COPY --from=src /src/gcc-core-3.3.4.tar.gz /src/gcc-g++-3.3.4.tar.gz /tmp/
RUN cd /tmp \
 && tar xzf gcc-core-3.3.4.tar.gz \
 && tar xzf gcc-g++-3.3.4.tar.gz \
 && mkdir gccbuild && cd gccbuild \
 && ../gcc-3.3.4/configure \
        --build=i686-pc-linux-gnu \
        --host=i686-pc-linux-gnu \
        --target=i686-pc-linux-gnu \
        --prefix=/usr/local/gcc334 \
        --program-suffix=-3.3.4 \
        --enable-languages=c,c++ \
        --disable-multilib --disable-nls --disable-shared \
 && sed -i 's|^#define HAVE_AS_LEB128 1|/* #undef HAVE_AS_LEB128 */|' gcc/auto-host.h \
 && ! grep -q '^#define HAVE_AS_LEB128' gcc/auto-host.h \
 && make MAKEINFO=true -j4 all-gcc \
 && make MAKEINFO=true install-gcc \
 && cd /tmp && rm -rf gcc-3.3.4 gccbuild gcc-*.tar.gz
RUN ln -sf /usr/local/gcc334/bin/gcc-3.3.4 /usr/local/bin/gcc \
 && ln -sf /usr/local/gcc334/bin/g++-3.3.4 /usr/local/bin/g++
ENV PATH=/usr/local/bin:/usr/local/gcc334/bin:$PATH

# The linker: H.J. Lu's binutils 2.14.90.0.6 (2003-08-20).
COPY --from=src /src/binutils-2.14.90.0.6 /tmp/binutils-2.14.90.0.6
RUN mkdir /tmp/bb && cd /tmp/bb \
 && export ac_cv_prog_LEX=flex ac_cv_prog_lex_root=lex.yy ac_cv_prog_lex_yytext_pointer=yes ac_cv_lib_fl_yywrap=yes \
 && ../binutils-2.14.90.0.6/configure --prefix=/opt/binutils-2.14.90.0.6 --disable-nls \
        --build=i686-pc-linux-gnu --host=i686-pc-linux-gnu --target=i686-pc-linux-gnu >/dev/null \
 && make -j4 all-ld >/dev/null \
 && make install-ld >/dev/null \
 && cd /tmp && rm -rf bb binutils-2.14.90.0.6 \
 && /opt/binutils-2.14.90.0.6/bin/ld --version | head -1

# The startup objects linked into every program on that system.
COPY crt /tmp/crt
RUN mkdir /opt/crt-2005 && cd /tmp/crt \
 && for f in start abi-note init crti crtn; do gcc -c -Wa,--traditional-format $f.S -o $f.o; done \
 && gcc -c -w -O2 -fno-pic -falign-functions=16 -fno-zero-initialized-in-bss -Wa,--traditional-format crtbegin.c \
 && gcc -c -w -O2 -fno-pic -falign-functions=16 -Wa,--traditional-format crtend.c \
 && ld -r -o /opt/crt-2005/crt1.o start.o abi-note.o init.o \
 && cp crti.o crtbegin.o crtend.o crtn.o /opt/crt-2005/ \
 && cd /tmp && rm -rf crt

WORKDIR /work
