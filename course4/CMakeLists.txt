cmake_minimum_required(VERSION 3.12)
project(course4)

set(CMAKE_CXX_STANDARD 17)

add_executable(course4 main.cpp ExEuclid.h ExEuclid.cpp Miller.h Miller.cpp QuickPow.h QuickPow.cpp RSA.cpp RSA.h)