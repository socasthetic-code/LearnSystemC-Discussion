# LearnSystemC Examples

Welcome to the examples directory! Since SystemC is a compiled C++ library, you cannot just run it in the browser. You must download these examples to your local machine to compile and run them.

## Requirements
Before attempting to compile these examples, ensure you have:
1. A C++14 (or newer) compatible compiler (GCC, Clang, or MSVC).
2. [CMake](https://cmake.org/download/) installed (version 3.10+).
3. The Accellera SystemC library compiled and installed on your system.

*If you do not have SystemC installed, please read [Installation & Setup](https://learn-systemc.com/tutorials/002-installation-and-setup).*

## Structure
Each sub-folder in this directory represents an independent, compilable SystemC project.
- `01_hello_world/`: The absolute basics of starting the SystemC simulation kernel.
- `02_virtual_platform/`: A small TLM-style platform shape.
- `03_modules_processes/`: Modules, processes, and scheduler basics.
- `04_ports_signals/`: Ports, signals, and channel binding.
- `05_tlm_basics/`: Basic TLM transaction flow.
- `06_cci_config/`: CCI presets, broker lookup, and unconsumed-preset validation.
- `07_systemc_ams/`: AMS modeling entry point.
- `08_uvm_systemc/`: UVM-SystemC starter shape for components, phases, and reports.
- `09_hls_subset/`: HLS-oriented SystemC subset example with clocked behavior.

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

## CCI Example Note

The `06_cci_config` example uses both SystemC and the SystemC CCI proof-of-concept library:

```bash
cmake .. -DSystemC_ROOT=/usr/local/systemc -DSystemCCCI_ROOT=/usr/local/systemc-cci
```

It intentionally creates one misspelled preset name so you can see how a platform can detect unconsumed configuration values before simulation results become misleading.
