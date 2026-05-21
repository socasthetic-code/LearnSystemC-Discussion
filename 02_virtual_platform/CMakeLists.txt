cmake_minimum_required(VERSION 3.10)
project(VirtualPlatform CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SystemC CONFIG REQUIRED)

add_executable(vp_sim main.cpp)
target_link_libraries(vp_sim PRIVATE SystemC::systemc)
