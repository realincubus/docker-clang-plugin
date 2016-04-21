#!/bin/bash

cd ~ 
cd clang_plugin_tests 
export PATH=$HOME/pet_install/:$PATH && \
export PATH=$HOME/pluto_install/:$PATH && \
export PATH=$HOME/build/:$PATH && \
git pull 
cmake .
ctest . 
cd ~ 
cd pluto 
make test 
