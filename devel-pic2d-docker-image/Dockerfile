############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         ├─incubus/plugin
#           ├─incubus/ycm
#             ├─incubus/devel

FROM incubus/devel
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S gcc-fortran hdf5-openmpi blas lapack tcsh && \ 
    pacman --noconfirm --force -Scc 

COPY superlu_4.3.tar.gz /superlu_4.3.tar.gz

RUN cd /tmp && \
    tar -xvf /superlu_4.3.tar.gz && \
    cd SuperLU_4.3 && \
    ./bootstrap && \
    make -j 5 && \
    make install


ADD pic2d /root/pic2d
ADD ycm_extra_conf.py /root/pic2d/.ycm_extra_conf.py

RUN cd $HOME/pic2d/src && \
    ./bootstrap.sh HEMP && \
    make -j 4 
    
