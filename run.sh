#!/bin/bash

#script som builder alle de create-image, kernel og module-stdlib før den kjører qemu

cmake --build build_group_1 --target uia-os-create-image
cmake --build build_group_1 --target uia-os-kernel
cmake --build build_group_1 --target uia-os-module-stdlib
qemu-system-i386 -gdb tcp::1234 -boot d -hda build_group_1/kernel.img -m 64 -hdb build_group_1/disk.iso -soundhw pcspk
