mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j24
cd ..
./build/bin/SimpleNetTest ./data/mnist/test/9/1045.png
