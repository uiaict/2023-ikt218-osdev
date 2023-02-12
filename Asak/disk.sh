#!/bin/bash

IMAGE_NAME=$1
dd if=/dev/zero of=$IMAGE_NAME bs=512 count=32768
parted $IMAGE_NAME mklabel msdos 
parted $IMAGE_NAME mkpart primary fat16 0% 100%

mv $IMAGE_NAME /home/asleirdal/ikt218-osdev/Asak/$IMAGE_NAME
