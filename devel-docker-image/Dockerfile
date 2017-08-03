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

FROM incubus/ycm-large
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    #pacman --noconfirm --force -Syu && \
    pacman --noconfirm -S zsh && \
    pacman --noconfirm --force -Scc
 

ADD bashrc /root/.bashrc
ADD bashrc /root/.zshrc
ADD update_all_repos /usr/local/bin/
ADD check_upload_state.sh /root/
ADD update_all.sh /root/
RUN git config --global credential.helper cache '--timeout=10000'

RUN cd $HOME/.vim/bundle/ && \
    git clone --depth=1 https://github.com/SirVer/ultisnips.git && \
    git clone --depth=1 https://github.com/realincubus/vim-snippets && \
    git clone --depth=1 https://github.com/rhysd/vim-clang-format
    
