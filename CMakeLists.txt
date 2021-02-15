# Set Required cmake version
cmake_minimum_required(VERSION 3.16)

# set project's name and language name to use
project(csv2obj CXX)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(application)
