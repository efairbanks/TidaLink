cp ./oscpack/ip/posix/UdpSocket.cpp ./oscpack/ip/UdpSocket.cpp
cp ./oscpack/ip/posix/NetworkingUtils.cpp ./oscpack/ip/NetworkingUtils.cpp
cd ./link
git submodule update --init --recursive
cmake .
cd ..
mkdir -p build
cd ./build
rm -rf *
cmake ..
make
