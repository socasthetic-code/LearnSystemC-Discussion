#include <systemc>
#include <iostream>

// All SystemC modules and objects live in the sc_core namespace.
// Using this namespace saves us from typing sc_core::sc_module everywhere.
using namespace sc_core;

int sc_main(int argc, char* argv[]) {
    // 1. sc_main is the entry point for a SystemC program, replacing the standard C++ main().
    
    std::cout << "Initializing SystemC Simulation..." << std::endl;

    // 2. Start the simulation kernel.
    // Since we have no modules or threads, the simulation will immediately exit.
    sc_start();

    std::cout << "Simulation Completed Successfully!" << std::endl;

    // 3. Return 0 to indicate success to the operating system.
    return 0;
}
