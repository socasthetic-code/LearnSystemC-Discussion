#include <systemc>
#include <iostream>

// A simple module demonstrating SC_METHOD and SC_THREAD
class MyModule : public sc_core::sc_module {
public:
    SC_HAS_PROCESS(MyModule);

    MyModule(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        // Register a Method (Non-yielding)
        SC_METHOD(my_method);
        dont_initialize();
        sensitive << my_event;

        // Register a Thread (Yielding)
        SC_THREAD(my_thread);
    }

private:
    sc_core::sc_event my_event;

    void my_method() {
        std::cout << "@" << sc_core::sc_time_stamp() 
                  << " - [METHOD] Woken up by my_event!" << std::endl;
    }

    void my_thread() {
        std::cout << "@" << sc_core::sc_time_stamp() 
                  << " - [THREAD] Booting up..." << std::endl;
        
        while(true) {
            wait(10, sc_core::SC_NS); // Yield control to the kernel
            std::cout << "@" << sc_core::sc_time_stamp() 
                      << " - [THREAD] Triggering my_event." << std::endl;
            my_event.notify();
            
            // Exit after 50ns
            if (sc_core::sc_time_stamp() >= sc_core::sc_time(50, sc_core::SC_NS)) {
                std::cout << "Ending simulation." << std::endl;
                sc_core::sc_stop();
            }
        }
    }
};

int sc_main(int argc, char* argv[]) {
    MyModule mod("my_module_instance");
    
    std::cout << "Starting Simulation..." << std::endl;
    sc_core::sc_start();
    
    return 0;
}
