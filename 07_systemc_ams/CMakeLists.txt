cmake_minimum_required(VERSION 3.10)
project(SystemCAMSExample CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This assumes systemc-ams was installed and is discoverable
find_package(SystemC CONFIG REQUIRED)
# In reality, you'd also need a find_package for SystemC-AMS or link it manually.
# target_link_libraries(ams_sim PRIVATE SystemC::systemc systemc-ams)

add_executable(ams_sim main.cpp)
target_link_libraries(ams_sim PRIVATE SystemC::systemc)
