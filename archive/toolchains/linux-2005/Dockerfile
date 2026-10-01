# The build machine of the Linux server 1.0 binary: Red Hat Linux 6.0 (glibc 2.1.1, egcs 1.1.2)
# with gcc 3.3.4 and binutils 2.14.90.0.x installed on top, as the binary records it.
#   docker build --platform linux/386 --build-arg JOBS=$(nproc) -t cod2engine-linux-2005 archive/toolchains/linux-2005
# See README.md for the evidence behind each piece.

# Fetch and check everything on a current system. The Red Hat 6.0 packages are read out of
# the release CD image on archive.org by byte range (rpms.txt: name, offset, size, sha256).
FROM debian:trixie-slim AS src
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates flex bison rpm2cpio cpio
WORKDIR /src
RUN curl -fsSLO https://ftpmirror.gnu.org/gcc/gcc-3.3.4/gcc-core-3.3.4.tar.gz \
 && curl -fsSLO https://ftpmirror.gnu.org/gcc/gcc-3.3.4/gcc-g++-3.3.4.tar.gz \
 && curl -fsSLO https://mirrors.edge.kernel.org/pub/linux/devel/binutils/binutils-2.14.90.0.6.tar.gz \
 && curl -fsSLO https://mirrors.edge.kernel.org/pub/linux/devel/binutils/binutils-2.14.90.0.8.tar.gz \
 && printf '%s  %s\n' \
    4cb79096cc37f45dcbac928db6e3c7f25dcea92f505bcdcda8dcc40105dd6759 gcc-core-3.3.4.tar.gz \
    976d3ee48f9c294fa35646222e4fb2260443b3083f6e9084bdb2631e5142ac5e gcc-g++-3.3.4.tar.gz \
    8757f67a0512ec1d55df55e35926be5faaa5ba3236f8f28b3f3dcdb613a41095 binutils-2.14.90.0.6.tar.gz \
    c4b9887f09dc29e3548db28942c3b7d7e467f91ab05d28d0b653995772eb8fa2 binutils-2.14.90.0.8.tar.gz \
    | sha256sum -c -
COPY rpms.txt /src/
RUN mkdir /rpms && while read name off size sum; do \
        curl -fsSL --retry 5 -r $off-$((off + size - 1)) -o /rpms/$name \
            'https://archive.org/download/PCP_0699/Red%20Hat%20Linux_i3.iso' \
        && echo "$sum  /rpms/$name" | sha256sum -c - || exit 1; \
    done < rpms.txt
# Unpacked here: Red Hat 6.0's tar hangs piping through gzip on current kernels.
# The ld snapshot ships no generated parser.
# libgcc is built without debug info: as 2.9.1 marks gcc 3.3's .debug_* sections allocatable.
RUN for f in *.tar.gz; do tar xzf $f && rm $f; done \
 && sed -i 's/^LIBGCC2_DEBUG_CFLAGS = -g$/LIBGCC2_DEBUG_CFLAGS = -g0/' gcc-3.3.4/gcc/Makefile.in \
 && cd binutils-2.14.90.0.6/ld && flex -oldlex.c ldlex.l && bison -y -d -o ldgram.c ldgram.y
# RPM scripts do not run here: ldconfig and the kernel-source link are done below.
RUN mkdir /rootfs && cd /rootfs && for r in /rpms/*.rpm; do rpm2cpio $r | cpio -idmu --quiet; done \
 && ln -sfn linux-2.2.5 usr/src/linux

FROM scratch AS base
COPY --from=src /rootfs /
RUN ["/sbin/ldconfig"]
ENV PATH=/usr/local/bin:/usr/bin:/bin LC_ALL=C
SHELL ["/bin/bash", "-c"]

FROM base
# uname reports the host kernel (x86_64): pin the triplet for every configure.
ENV TRIPLET="--build=i686-pc-linux-gnu --host=i686-pc-linux-gnu --target=i686-pc-linux-gnu"
ARG JOBS=4
# The linker: H.J. Lu's binutils 2.14.90.0.6 (2003-08-20). It is on PATH while gcc is built,
# which gives libstdc++ its symbol versions (GLIBCPP_3.2, CXXABI_1.2).
COPY --from=src /src/binutils-2.14.90.0.6 /tmp/binutils-2.14.90.0.6
RUN mkdir /tmp/bld && cd /tmp/bld \
 && ../binutils-2.14.90.0.6/configure --disable-nls $TRIPLET >/dev/null \
 && make all-ld >/dev/null && make install-ld >/dev/null \
 && cd / && rm -rf /tmp/bld /tmp/binutils-2.14.90.0.6 && ld --version | head -1

# gcc 3.3.4, configured with Red Hat's as 2.9.1: it finds no .uleb128 (udata4 call sites in
# .gcc_except_table) and puts --traditional-format in its assembler spec (advance_loc4 FDEs).
# Everything below is built without debug info (see libgcc above).
ENV NODEBUG="BOOT_CFLAGS=-O2 CFLAGS_FOR_TARGET=-O2 CXXFLAGS_FOR_TARGET=-O2"
COPY --from=src /src/gcc-3.3.4 /tmp/gcc-3.3.4
RUN mkdir /tmp/bld && cd /tmp/bld \
 && ../gcc-3.3.4/configure $TRIPLET \
        --enable-languages=c,c++ >/dev/null \
 && ! grep -q '^#define HAVE_AS_LEB128' gcc/auto-host.h \
 && { make -j$JOBS bootstrap MAKEINFO=true $NODEBUG >/tmp/gcc.log 2>&1 || { tail -30 /tmp/gcc.log; false; }; } && make install MAKEINFO=true $NODEBUG >/dev/null \
 && cd / && rm -rf /tmp/bld /tmp/gcc-* && /sbin/ldconfig && gcc --version | head -1

# The game code's assembler: gas 2.14.90.0.8 or later (earlier ones lay out local statics in
# .bss in a different order).
COPY --from=src /src/binutils-2.14.90.0.8 /tmp/binutils-2.14.90.0.8
RUN mkdir /tmp/bld && cd /tmp/bld \
 && CFLAGS=-O2 ../binutils-2.14.90.0.8/configure --disable-nls $TRIPLET >/dev/null \
 && make all-gas >/dev/null && make install-gas >/dev/null \
 && cd / && rm -rf /tmp/bld /tmp/binutils-* && as --version | head -1

WORKDIR /work
