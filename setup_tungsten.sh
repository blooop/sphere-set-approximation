#!/bin/bash 


mkdir 3rd_party
cd 3rd_party  
git clone git@github.com:tunabrain/tungsten.git
cd tungsten
./setup_builds.sh

cd build/release
make -j
echo "alias tungsten="/workspaces/sphere-set-approximation/3rd_party/tungsten/build/release/tungsten"" >> ~/.bashrc
source ~/.bashrc
tungsten example/armadillo.json

