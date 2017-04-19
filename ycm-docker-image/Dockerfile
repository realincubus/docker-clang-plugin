############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/plugin
#         ├─incubus/plugin-tests

FROM incubus/plugin-tests
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -Syu && \
    pacman --noconfirm -S vim ncurses && \
    pacman --noconfirm --force -Scc
 
# install pathogen
RUN mkdir -p ~/.vim/autoload ~/.vim/bundle && \
    curl -LSso ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim

COPY ycm_patch /root/ycm_patch

# i choose not in install python3 which is standard for 
# arch this is why /usr/bin/env does not return the pyhton interpreter 
# if /usr/bin/python is not linked to python2
#TODO setup paths for libclang 
RUN cd ~/.vim/bundle && \
    ln -s /usr/bin/python2 /usr/bin/python && \
    export PATH=$HOME/install/:$PATH && \
    export PATH=$HOME/install/lib:$PATH && \
    git clone --depth=1 https://github.com/Valloric/YouCompleteMe.git && \
    cd YouCompleteMe && \
    git submodule update --init --recursive && \
    cd ~/.vim/bundle/YouCompleteMe/third_party/ycmd/ && \
    patch -p1 < ~/ycm_patch && \
    cd ~/.vim/bundle/YouCompleteMe/ && \
    ./install.py --clang-completer --system-libclang


COPY pathogen_minimal.vimrc /root/.vimrc

# setup example folder
RUN mkdir /root/example

ADD CMakeLists.txt /root/example/
ADD main.cpp /root/example/
ADD ycm_extra_conf.py /root/example/.ycm_extra_conf.py

ADD bashrc /root/.bashrc

# initialize the example project

RUN cd ~ && \
    cd example && \
    export PATH=$HOME/pet_install/:$PATH && \
    export PATH=$HOME/pluto_install/:$PATH && \
    export LD_LIBRARY_PATH=$HOME/pluto_install/lib/:$LD_LIBRARY_PATH && \
    export PATH=$HOME/install/:$PATH && \
    export PATH=$HOME/install/lib:$PATH && \
    export PATH=$HOME/install/bin:$PATH && \
    export PATH=$HOME/ClanPlugin/:$PATH && \
    export PATH=$HOME/ClanPlugin/lib:$PATH && \
    CC=clang CXX=clang++ cmake . && \
    make 

