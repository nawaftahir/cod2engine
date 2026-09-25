# gcc/g++ 3.3.4 as configured on the original Linux build machine.
#   docker build --platform linux/386 -t cod2engine-gcc334 toolchains/gcc-3.3.4
#
# Debian sarge provides the host tools, including GNU as 2.15.
# gcc is built without HAVE_AS_LEB128: the original .gcc_except_table uses
# udata4 call-site entries, which gcc 3.3 emits only when configure found an
# assembler without .uleb128 support.

# Fetch and check the sources on a current system (sarge has no sha256sum or modern TLS).
FROM debian:trixie-slim AS src
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates \
 && cd /tmp \
 && curl -fsSLO https://ftpmirror.gnu.org/gcc/gcc-3.3.4/gcc-core-3.3.4.tar.gz \
 && curl -fsSLO https://ftpmirror.gnu.org/gcc/gcc-3.3.4/gcc-g++-3.3.4.tar.gz \
 && echo "4cb79096cc37f45dcbac928db6e3c7f25dcea92f505bcdcda8dcc40105dd6759  gcc-core-3.3.4.tar.gz" | sha256sum -c - \
 && echo "976d3ee48f9c294fa35646222e4fb2260443b3083f6e9084bdb2631e5142ac5e  gcc-g++-3.3.4.tar.gz" | sha256sum -c -

FROM debian/eol:sarge

RUN apt-get update && apt-get install -y build-essential binutils make libncurses5-dev \
 && rm -rf /var/lib/apt/lists/*

COPY --from=src /tmp/gcc-core-3.3.4.tar.gz /tmp/gcc-g++-3.3.4.tar.gz /tmp/
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
 && make MAKEINFO=true -j"$(nproc)" all-gcc \
 && make MAKEINFO=true install-gcc \
 && cd /tmp && rm -rf gcc-3.3.4 gccbuild gcc-*.tar.gz

RUN ln -sf /usr/local/gcc334/bin/gcc-3.3.4 /usr/local/bin/gcc \
 && ln -sf /usr/local/gcc334/bin/g++-3.3.4 /usr/local/bin/g++
ENV PATH=/usr/local/bin:/usr/local/gcc334/bin:$PATH
WORKDIR /work
