#!/bin/sh
./configure \
--disable-static \
--enable-asm \
--cpu=cortex-a8 \
--arch=armv7 \
--enable-neon \
--enable-shared \
--enable-memalign-hack \
--disable-network \
--disable-muxers \
--disable-protocols \
--disable-demuxers \
--disable-encoders \
--disable-parsers \
--disable-bsfs \
--enable-gpl \
--enable-version3 \
--enable-nonfree \
--disable-doc \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffprobe \
--disable-ffserver \
--disable-avdevice \
--disable-devices \
--enable-small \
--cross-prefix=$ndk/toolchains/arm-linux-androideabi-4.4.3/prebuilt/windows/bin/arm-linux-androideabi- \
--enable-cross-compile \
--target-os=linux \
--extra-cflags='-I$ndk/platforms/android-9/arch-arm/usr/include -mfpu=neon -mfloat-abi=softfp' \
--extra-ldflags='-L$ndk/platforms/android-9/arch-arm/usr/lib -nostdlib' \
--arch=arm \
--disable-debug \
--disable-stripping \
--disable-armv5te \
--disable-armv6 \
--disable-armv6t2 \

sed -i 's/HAVE_LRINT 0/HAVE_LRINT 1/g' config.h
sed -i 's/HAVE_LRINTF 0/HAVE_LRINTF 1/g' config.h
sed -i 's/HAVE_ROUND 0/HAVE_ROUND 1/g' config.h
sed -i 's/HAVE_ROUNDF 0/HAVE_ROUNDF 1/g' config.h
sed -i 's/HAVE_TRUNC 0/HAVE_TRUNC 1/g' config.h
sed -i 's/HAVE_TRUNCF 0/HAVE_TRUNCF 1/g' config.h
sed -i 's/HAVE_SYMVER 1/HAVE_SYMVER 0/g' config.h
