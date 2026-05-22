cmake_minimum_required(VERSION 3.10)
project(CCIConfigExample CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SystemC CONFIG REQUIRED)
find_package(SystemCCCI CONFIG REQUIRED)

add_executable(cci_sim main.cpp)
target_link_libraries(cci_sim PRIVATE SystemC::systemc SystemC::cci)
