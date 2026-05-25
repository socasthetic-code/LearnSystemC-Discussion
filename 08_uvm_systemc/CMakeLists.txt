cmake_minimum_required(VERSION 3.10)
project(UVMSystemCStarter CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SystemC CONFIG REQUIRED)

# UVM-SystemC package exports differ across installations. If your local
# installation provides a CMake package, add it here and link the target.
set(UVMSystemC_ROOT "" CACHE PATH "Optional UVM-SystemC installation prefix")
add_executable(uvm_systemc_starter main.cpp)
target_link_libraries(uvm_systemc_starter PRIVATE SystemC::systemc)
