#!/bin/bash -xe 

cd ~/ClanPlugin
git remote update
git status -uno

cd ~/pluto
git remote update
git status -uno

cd ~/pluto/pluto_codegen_cxx
git remote update
git status -uno

cd ~/pet
git remote update
git status -uno

cd ~/libclang-to-pssl
git remote update 
git status -uno

cd ~/clang_plugin_tests
git remote update 
git status -uno

