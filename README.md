# csv2obj
This software can generate Wavefront .obj file from CSV 2D Curve file.

## Before the installation
This software requires at least CMake version 3.16 to build. Check your CMake version with following command.
```
cmake --version
```

## Installation
* Copy and paste following command to download source codes from repository.  
```
git clone https://github.com/Konishi2911/csv2obj.git
```  
* Make a directory to prepare to build.  
```
cd csv2obj
mkdir build
cd build
```  
* Build and install.  
```
cmake ..
make
make install
```  

## Uninstallation
* Ubuntu 20.04.2 LTS
```
sudo rm -r /usr/local/bin/csv2obj/
```
