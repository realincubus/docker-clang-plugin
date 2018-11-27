############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         ├─incubus/plugin
#           ├─incubus/devel-turbovnc

FROM compus.physik.uni-greifswald.de:5000/kemnitzs/devel-turbovnc
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Su pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S \
	boost gtkmm3 gtksourceview3 gtksourceviewmm aspell lldb libgit2 pkg-config  && \
    pacman --noconfirm --force -Scc

ADD bashrc /data/bashrc

# fake install libclang
RUN cp /root/install/lib/libclang.so* /usr/lib/  && \
    ln -s /usr/lib/libclang.so /usr/lib/libclang.so.4 && \
    ln -s /usr/lib/libclang.so /usr/lib/libclang.so.4.0 && \
    cp -r /root/install/include/* /usr/include 

RUN cd ~ && \
    git clone --depth=1 --recursive https://github.com/cppit/jucipp.git && \
    cd jucipp && \
    mkdir build_release && \
    cd build_release && \
    cmake ..

ADD juci.patch /data/juci.patch 

RUN cd ~/jucipp/ && \
    git apply /data/juci.patch
    
# TODO fuse
RUN cd ~/jucipp/build_release && \
    make -j 4 && \
    make install 

ADD turboscript /turboscript_jucipp

ADD example /data/example
