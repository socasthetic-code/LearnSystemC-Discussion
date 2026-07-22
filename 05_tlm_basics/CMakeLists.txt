cmake_minimum_required(VERSION 3.10)
project(TLMBasicsExample CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SystemC CONFIG REQUIRED)

add_executable(tlm_sim main.cpp)
target_link_libraries(tlm_sim PRIVATE SystemC::systemc)
