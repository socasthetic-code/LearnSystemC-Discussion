cmake_minimum_required(VERSION 3.10)
project(HelloWorldSystemC CXX)

# Require C++14 or newer for modern SystemC
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SystemC package. 
# This requires that the user passed -DSystemC_ROOT=/path/to/systemc during cmake generation
find_package(SystemC CONFIG REQUIRED)

# Add our executable
add_executable(hello_world main.cpp)

# Link the target against SystemC
target_link_libraries(hello_world PRIVATE SystemC::systemc)
