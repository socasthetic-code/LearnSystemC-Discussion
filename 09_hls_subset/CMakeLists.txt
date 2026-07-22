cmake_minimum_required(VERSION 3.10)
project(HLSSubsetCounter CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SystemC CONFIG REQUIRED)

add_executable(hls_subset_counter main.cpp)
target_link_libraries(hls_subset_counter PRIVATE SystemC::systemc)
