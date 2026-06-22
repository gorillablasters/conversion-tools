cmake_minimum_required(VERSION 3.16)
project(zconvert VERSION 1.0 LANGUAGES CXX)

add_executable(zconvert src/main.cpp)
target_compile_features(zconvert PRIVATE cxx_std_17)
