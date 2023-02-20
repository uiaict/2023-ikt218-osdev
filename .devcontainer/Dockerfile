FROM dorowu/ubuntu-desktop-lxde-vnc

RUN wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add -

# Install newest cmake
RUN apt-get update && sudo apt-get install -y software-properties-common lsb-release -y
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
RUN apt-get update && apt-get install kitware-archive-keyring && rm /etc/apt/trusted.gpg.d/kitware.gpg
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 6AF7F09730B3F0A4

# Following Part 3 - Installing Build Dependencies and Getting Started
RUN apt-get update --allow-insecure-repositories && sudo apt install g++-multilib gcc-multilib git cmake nasm grub-common grub-pc-bin xorriso qemu qemu-kvm gdb bochsbios vgabios git libgtk2.0-dev -y

# https://people.engr.tamu.edu/bettati/Courses/OSProjects/to-use-gdb-tools.pdf
RUN apt-get install --allow-unauthenticated libsdl2-dev libncurses5-dev libx11-dev libxext-dev -y
RUN sudo	apt-get	remove	bochs
RUN wget https://sourceforge.net/projects/bochs/files/bochs/2.6.11/bochs-2.6.11.tar.gz/download -O bochs.tar.gz  && tar -xvf bochs.tar.gz
RUN cd bochs-2.6.11 && sh .conf.linux --enable-gdb-stub
RUN cd bochs-2.6.11 && make -j && make install

