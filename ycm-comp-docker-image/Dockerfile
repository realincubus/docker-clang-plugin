############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/plugin
#         ├─incubus/ycm

FROM incubus/ycm-large
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

RUN mkdir $HOME/libs/ && \
    cp -a $HOME/ClanPlugin/lib/ClanPlugin.so* $HOME/libs/ && \
    cp -a $HOME/install/lib/libclang.so* $HOME/libs/ && \
    cp -a $HOME/pet_install/lib/libisl*.so* $HOME/libs/ && \
    cp -a $HOME/pluto_install/lib/lib*.so* $HOME/libs/ && \
    rm -rf $HOME/llvm $HOME/build $HOME/ClanPlugin $HOME/pet $HOME/pet_install $HOME/pluto $HOME/pluto_install && \
    rm -rf $HOME/.vim/bundle/YouCompleteMe/.git /usr/share/locale/* && \
    pacman --noconfirm -Rs git ninja grep sed patch bison flex autogen autoconf automake  libyaml intel-tbb

COPY bashrc /root/.bashrc
COPY CMakeLists.txt /root/example/CMakeLists.txt

# somehow i have to do this 
RUN source $HOME/.bashrc && \
    cd $HOME/example && \
    make 
    
