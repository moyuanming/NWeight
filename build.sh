#!/bin/sh
rm -f config.cache config.status

CC=/crosstools/rhy_tools/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-gcc \
CPP=/crosstools/rhy_tools/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-cpp \
LD=/crosstools/rhy_tools/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-ld \
AR=/crosstools/rhy_tools/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-ar \
RANLIB=/crosstools/rhy_tools/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-ranlib \
STRIP=/crosstools/rhy_tools/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-strip \
./configure --prefix=/root/EMRCV3/ \
    --build=i686-linux \
    --host=arm-linux \
    --target=arm-linux 
