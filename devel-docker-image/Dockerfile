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

FROM incubus/ycm
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    #pacman --noconfirm --force -Syu && \
    pacman --noconfirm -S zsh && \
    pacman --noconfirm --force -Scc
 

COPY bashrc /root/.bashrc
COPY bashrc /root/.zshrc
COPY update_all_repos /usr/local/bin/
COPY check_upload_state.sh /root/
COPY update_all.sh /root/
RUN git config --global credential.helper cache '--timeout=10000'

RUN cd $HOME/.vim/bundle/ && \
    git clone https://github.com/SirVer/ultisnips.git && \
    git clone https://github.com/realincubus/vim-snippets && \
    git clone https://github.com/rhysd/vim-clang-format
    
