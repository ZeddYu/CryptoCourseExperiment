cmake_minimum_required(VERSION 3.12)
project(course5)

set(CMAKE_CXX_STANDARD 17)

set(INC_DIR /usr/local/include)

include_directories(${INC_DIR})
link_libraries(NTL)

link_libraries(gmp)

add_executable(course5 main.cpp sha1.cpp sha1.h)
target_link_libraries(course5 NTL)
target_link_libraries(course5 gmp)