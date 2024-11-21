mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j
./main ../example/armadillo.obj ../example/armadillo.json

