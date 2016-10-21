############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux

FROM base/archlinux
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -Syu pacman && \
    pacman --noconfirm --force -S git gcc cmake make curl msgpack-c libuv unibilium libtermkey libvterm lua51 jemalloc lua51 lua51-lpeg lua51-mpack lua51-bitop gperf python python-pip && \
    pacman --noconfirm --force -Scc 

RUN curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim 

RUN cd $HOME && \
    git clone https://github.com/neovim/neovim.git && \
    cd neovim && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install 

RUN pip3 install --upgrade neovim

RUN cd $HOME && \
    mkdir -p .vim/plugged && \
    cd .vim/plugged && \
    git clone https://github.com/Valloric/YouCompleteMe.git && \
    cd YouCompleteMe && \
    git submodule update --init --recursive && \
    python install.py --clang-completer 

COPY init.vim /root/.config/nvim/init.vim

ADD example /root/example

RUN cd ~ && \
    cd example && \
    cmake .

