# LearnSystemC Examples

Welcome to the examples directory! Since SystemC is a compiled C++ library, you cannot just run it in the browser. You must download these examples to your local machine to compile and run them.

## Requirements
Before attempting to compile these examples, ensure you have:
1. A C++14 (or newer) compatible compiler (GCC, Clang, or MSVC).
2. [CMake](https://cmake.org/download/) installed (version 3.10+).
3. The Accellera SystemC library compiled and installed on your system.

*If you do not have SystemC installed, please read [Tutorial 0.2: Installation & Setup](https://learnsystemc.in/tutorials/01-systemc-installation).*

## Structure
Each sub-folder in this directory represents an independent, compilable SystemC project.
- `01_hello_world/`: The absolute basics of starting the SystemC simulation kernel.
- *(More examples matching the website chapters will be added here!)*

## Compiling an Example

### On Linux / macOS
```bash
cd 01_hello_world
mkdir build && cd build

# Tell CMake where your SystemC installation is located
cmake .. -DSystemC_ROOT=/usr/local/systemc 

make
./hello_world
```

### On Windows
```bash
cd 01_hello_world
mkdir build && cd build

# Generate Visual Studio project files
cmake .. -DSystemC_ROOT=C:\systemc

# Build it
cmake --build . --config Release

# Run it
Release\hello_world.exe
```
