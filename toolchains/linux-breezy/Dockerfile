# The build machine of the Linux server 1.2c/1.3 binaries: Ubuntu 5.10 "breezy", i386,
# with gcc-3.3 3.3.6-8ubuntu1 (game code) and gcc-3.4 3.4.4-6ubuntu8 (startup objects),
# as the binaries' .comment sections record. Packages come from old-releases.ubuntu.com.
#   docker build --platform linux/386 -t cod2engine-linux-breezy toolchains/linux-breezy
# 1.3 was linked after breezy's glibc security update:
#   docker build --platform linux/386 --build-arg LIBC6=2.3.5-1ubuntu12.5.10.1 \
#       -t cod2engine-linux-breezy-1.3 toolchains/linux-breezy
ARG LIBC6=2.3.5-1ubuntu12

FROM debian:trixie AS bootstrap
ARG LIBC6
RUN apt-get update -qq && apt-get install -y -qq debootstrap
# breezy's archive keys expired long ago; the pool is pinned by exact package versions below
RUN debootstrap --arch=i386 --variant=buildd --no-check-gpg \
	--include=gcc-3.3,g++-3.3,gcc-3.4,g++-3.4,libstdc++5-3.3-dev,make \
	breezy /rootfs http://old-releases.ubuntu.com/ubuntu
RUN if [ "$LIBC6" != 2.3.5-1ubuntu12 ]; then \
	for p in libc6 libc6-dev; do \
		wget -q -P /rootfs/tmp http://old-releases.ubuntu.com/ubuntu/pool/main/g/glibc/${p}_${LIBC6}_i386.deb || exit 1; \
	done && chroot /rootfs dpkg -i /tmp/libc6_${LIBC6}_i386.deb /tmp/libc6-dev_${LIBC6}_i386.deb \
	&& rm /rootfs/tmp/*.deb; fi

FROM scratch
ARG LIBC6
COPY --from=bootstrap /rootfs /
RUN dpkg-query -W gcc-3.3 g++-3.3 gcc-3.4 binutils libc6-dev | tee /toolchain.versions \
	&& grep -q '3.3.6-8ubuntu1' /toolchain.versions && grep -q '3.4.4-6ubuntu8$' /toolchain.versions \
	&& grep -q "libc6-dev	$LIBC6\$" /toolchain.versions
ENV LC_ALL=C
