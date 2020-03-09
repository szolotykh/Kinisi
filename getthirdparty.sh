#!/bin/sh

# Install dependency

# GIT
apt-get install git

# CMake
apt-get install cmake

# Build essential
apt-get install build-essential
gcc -v
make -v

# SSL
apt-get install libssl-dev

# Directories
RootDir=$PWD
ThirdpartyDir="$RootDir/thirdparty"
DownloadsDir="$ThirdpartyDir/downloads"
mkdir $ThirdpartyDir
mkdir $DownloadsDir

# gtest
echo "Clonning gtest"
if [ ! -d "$ThirdpartyDir/googletest" ]; then
    git clone https://github.com/google/googletest.git $ThirdpartyDir/googletest

    echo "Building gtest"
    cd $ThirdpartyDir/googletest
    cmake .
    cmake --build . --target install
else
    echo "googletest exists"
fi


# paho
echo "Clonning paho.c"
if [ ! -d "$ThirdpartyDir/paho.c" ]; then
    git clone https://github.com/eclipse/paho.mqtt.c $ThirdpartyDir/paho.c
    echo "Building paho.c"
    cd $ThirdpartyDir/paho.c
    cmake -Bbuild -H. -DPAHO_WITH_SSL=ON -DPAHO_ENABLE_TESTING=OFF
    cmake --build build/ --target install
else
    echo "paho exists"
fi

# configure dynamic linker run-time bindings
ldconfig

echo "Clonning paho.cpp"
if [ ! -d "$ThirdpartyDir/paho.cpp" ]; then
    git clone https://github.com/eclipse/paho.mqtt.cpp $ThirdpartyDir/paho.cpp
    echo "Building paho.cpp"
    cd $ThirdpartyDir/paho.cpp
    cmake -Bbuild -H. -DPAHO_BUILD_DOCUMENTATION=FALSE -DPAHO_BUILD_SAMPLES=FALSE
    sudo cmake --build build/ --target install
else
    echo "paho exists"
fi


# configure dynamic linker run-time bindings
ldconfig

# Phidgets
# libusb-1.0 for phidgets
# https://www.phidgets.com/docs/OS_-_Linux
apt-get install libusb-1.0-0-dev

cd $ThirdpartyDir
if [ -z $(ls | grep libphidget22) ]; then
    cd $DownloadsDir
    wget https://www.phidgets.com/downloads/phidget22/libraries/linux/libphidget22.tar.gz
    tar xvzf ./libphidget22.tar.gz -C "$ThirdpartyDir"

    cd $ThirdpartyDir
    cd ./$(ls | grep libphidget22)
    ./configure
    make
    make install
else
    echo "libphidget22 exists"
fi


#JSON 11
echo "Clonning json11"
if [ ! -d "$ThirdpartyDir/json11" ]; then
    git clone https://github.com/dropbox/json11.git $ThirdpartyDir/json11
    echo "Building json11"
    cd $ThirdpartyDir/json11
    mkdir build
    cd $ThirdpartyDir/json11/build
    cmake ..
    cmake --build . --target install
else
    echo "json11 exists"
fi

# Cleaning up
cd $PWD
rm -r $ThirdpartyDir

exit 0