# The build machine of the Linux server 1.2c/1.3 binaries: Ubuntu 5.10 "breezy", i386,
# with gcc-3.3 3.3.6-8ubuntu1 (game code) and gcc-3.4 3.4.4-6ubuntu8 (startup objects),
# as the binaries' .comment sections record. Packages come from old-releases.ubuntu.com.
#   docker build --platform linux/386 -t cod2engine-linux-breezy toolchains/linux-breezy
FROM debian:trixie AS bootstrap
RUN apt-get update -qq && apt-get install -y -qq debootstrap
# breezy's archive keys expired long ago; the pool is pinned by exact package versions below
RUN debootstrap --arch=i386 --variant=buildd --no-check-gpg \
	--include=gcc-3.3,g++-3.3,gcc-3.4,g++-3.4,libstdc++5-3.3-dev,make \
	breezy /rootfs http://old-releases.ubuntu.com/ubuntu

FROM scratch
COPY --from=bootstrap /rootfs /
RUN dpkg-query -W gcc-3.3 g++-3.3 gcc-3.4 binutils libc6-dev | tee /toolchain.versions \
	&& grep -q '3.3.6-8ubuntu1' /toolchain.versions && grep -q '3.4.4-6ubuntu8$' /toolchain.versions
ENV LC_ALL=C
