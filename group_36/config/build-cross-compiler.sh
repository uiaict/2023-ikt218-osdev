#!/bin/bash
BUILD_PATH=cmake-build-debug
MUSL=$(realpath ../$BUILD_PATH/musl-cross)
MUSL_COMPILER=$(realpath ../musl-compiler)
mkdir -p ../$BUILD_PATH
mkdir -p $MUSL_COMPILER
echo $MUSL
if [ ! -d "$MUSL" ] ; then
    git clone https://github.com/richfelker/musl-cross-make.git $MUSL
fi


cat <<EOT >> $MUSL/config.mak
TARGET = i386-linux-musl
OUTPUT = $MUSL_COMPILER
GCC_VER = 11.2.0
EOT


cd $MUSL && make && make install