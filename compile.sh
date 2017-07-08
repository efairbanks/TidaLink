cd ./link
git submodule update --init --recursive
cmake .
cd ..
mkdir -p build
cd ./build
rm -rf *
cmake ..
make
