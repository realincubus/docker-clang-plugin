############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         ├─incubus/plugin

FROM incubus/plugin
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Su pacman && \
    pacman-db-upgrade && \
    #pacman --noconfirm --force -Syu && \
    pacman --noconfirm -S \
	turbojpeg \
	cmake \
	lxde-common lxsession openbox && \
    pacman --noconfirm --force -Scc

RUN git clone https://github.com/TurboVNC/turbovnc.git /turbovnc && \
    cd /turbovnc && \
    cmake -DTJPEG_LIBRARY=/usr/lib/libturbojpeg.so -DTVNC_BUILDJAVA=0 -DTVNC_BUILDNATIVE=0 -DTVNC_USETLS=gnutls . && \
    make -j 4 && \
    make install && \
    cd .. && \
    rm -rf turbovnc

ADD turboscript /turboscript
    
CMD /turboscript  

ADD xinitrc /data/.xinitrc

# TODO move to usual install stuff
RUN pacman --noconfirm --force -S xorg-xauth xorg-xkbcomp xkeyboard-config
RUN pacman --noconfirm --force -S sudo xorg-server xorg-xinit xf86-video-vesa xterm

ADD restart /restart

ADD xstartup /tmp/xstartup.turbovnc

RUN pacman --noconfirm --force -S lxpanel

