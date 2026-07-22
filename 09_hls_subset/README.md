# SystemC HLS Subset Starter

This example keeps the model deliberately simple so you can reason about hardware generation:

- static module structure
- clocked process
- explicit reset behavior
- bounded storage
- no dynamic allocation in the process body

Actual HLS pragmas are vendor-specific, so this example focuses on portable SystemC subset style.

## Try It

```bash
mkdir build
cd build
cmake .. -DSystemC_ROOT=/usr/local/systemc
cmake --build .
./hls_subset_counter
```
