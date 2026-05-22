#include <systemc>
#include <cci_configuration>
#include <iostream>

class MyIP : public sc_core::sc_module {
public:
    // A CCI Parameter
    cci::cci_param<int> my_baud_rate;

    SC_HAS_PROCESS(MyIP);

    MyIP(sc_core::sc_module_name name) 
        : sc_core::sc_module(name),
          my_baud_rate("baud_rate", 9600, "The baud rate of the UART") 
    {
        SC_THREAD(run);
    }

private:
    void run() {
        std::cout << "@" << sc_core::sc_time_stamp() 
                  << " [MyIP] Booting up with baud rate: " 
                  << my_baud_rate.get_value() << std::endl;
        
        wait(10, sc_core::SC_NS);

        // We can check if it gets updated at runtime!
        std::cout << "@" << sc_core::sc_time_stamp() 
                  << " [MyIP] Current baud rate: " 
                  << my_baud_rate.get_value() << std::endl;
    }
};

int sc_main(int argc, char* argv[]) {
    // Before instantiating the module, we can use the CCI Broker to set the parameter globally!
    cci::cci_broker_handle broker = cci::cci_get_global_broker(cci::cci_originator("sc_main"));
    
    std::cout << "Setting baud_rate to 115200 via CCI Broker..." << std::endl;
    broker.set_preset_cci_value("uart_instance.baud_rate", cci::cci_value(115200));

    // Instantiate the module
    MyIP uart("uart_instance");

    std::cout << "Starting Simulation..." << std::endl;
    sc_core::sc_start();

    return 0;
}
