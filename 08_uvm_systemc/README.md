# UVM-SystemC Starter

This example is a compact starter for the UVM-SystemC lessons. It is intentionally small: the goal is to show the shape of a component, a phase-oriented run flow, and reporting.

UVM-SystemC package names and CMake package exports can vary by installation. If your installed kit uses a different package name, adjust `CMakeLists.txt` to match your local UVM-SystemC installation.

## Try It

```bash
mkdir build
cd build
cmake .. -DSystemC_ROOT=/usr/local/systemc -DUVMSystemC_ROOT=/usr/local/uvm-systemc
cmake --build .
./uvm_systemc_starter
```

## What to Look For

- where the test component is constructed
- where reporting happens
- how the example maps to UVM-SystemC component and phase lessons
