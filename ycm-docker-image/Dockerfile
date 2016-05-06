############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─realincubus/clang
#     ├─realincubus/pet
#       ├─realincubus/plugin

FROM realincubus/plugin
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

#TODO setup paths for libclang 
RUN cd ~/.vim/bundle && \
    export PATH=$HOME/install/:$PATH && \
    git clone https://github.com/Valloric/YouCompleteMe.git && \
    cd YouCompleteMe && \
    git submodule update --init --recursive && \
    cd ~/.vim/bundle/YouCompleteMe/ && \
    ./install.py --clang-completer --system-libclang


COPY pathogen_minimal.vimrc /root/.vimrc

# setup example folder
RUN mkdir /root/example

COPY CMakeLists.txt /root/example/
COPY main.cpp /root/example/
COPY ycm_extra_conf.py /root/example

COPY bashrc /root/.bashrc

# initialize the example project

RUN cd ~ && \
    cd example && \
    export PATH=$HOME/pet_install/:$PATH && \
    export PATH=$HOME/pluto_install/:$PATH && \
    export PATH=$HOME/install/:$PATH && \
    export PATH=$HOME/install/bin:$PATH && \
    export PATH=$HOME/ClanPlugin/:$PATH && \
    CC=clang CXX=clang++ cmake . && \
    make 
