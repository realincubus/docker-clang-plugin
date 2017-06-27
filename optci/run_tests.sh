#!/bin/bash -x
# TODO after proper install remove this 
# need all paths that we also have on command line
#export PATH=$HOME/install/bin/:$PATH
#export PATH=$HOME/pet_install/:$PATH
#export PATH=$HOME/pluto_install/:$PATH
#export PATH=$HOME/ClanPlugin/:$PATH

# to find the libraries
#export LD_LIBRARY_PATH=$HOME/install/lib/:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=$HOME/ClanPlugin/lib/:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=$HOME/pet_install/lib/:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=$HOME/pluto_install/lib/:$LD_LIBRARY_PATH

#export CPATH=$HOME/pluto_install/include/pluto/:$HOME/pluto_install/include/pluto_codegen_cxx:$HOME/pet_install/include/:$CPATH

cd /root/optci/unit_tests && ctest --no-compress-output -T Test .
rm -rf /host/*
cp -r /root/optci/unit_tests/Testing /host/optci_results
cp -r /root/optci /host/optci_results/optci
chmod 777 -R /host

