cp ./oscpack/ip/posix/UdpSocket.cpp ./oscpack/ip/UdpSocket.cpp
cp ./oscpack/ip/posix/NetworkingUtils.cpp ./oscpack/ip/NetworkingUtils.cpp
cd ./link
git submodule update --init --recursive
cmake .
cd ..
rm -rf build
mkdir -p build
cd build
cmake ..
make
