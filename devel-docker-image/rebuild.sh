#!/bin/bash

cd ..

cd pet-docker-image
./build
cd ..

cd pluto-docker-image
./build
cd ..

cd plugin-docker-image
./build
cd ..
cd ycm-docker-image
./build
cd ..

