#include <systemc>
#include <iostream>

// Producer Module
class Producer : public sc_core::sc_module {
public:
    sc_core::sc_out<int> out_port;

    SC_HAS_PROCESS(Producer);

    Producer(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        SC_THREAD(run);
    }

private:
    void run() {
        for (int i = 0; i < 5; ++i) {
            std::cout << "@" << sc_core::sc_time_stamp() << " [Producer] Writing: " << i << std::endl;
            out_port.write(i);
            wait(10, sc_core::SC_NS);
        }
    }
};

// Consumer Module
class Consumer : public sc_core::sc_module {
public:
    sc_core::sc_in<int> in_port;

    SC_HAS_PROCESS(Consumer);

    Consumer(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        SC_METHOD(run);
        sensitive << in_port; // Trigger whenever in_port's value changes
        dont_initialize();
    }

private:
    void run() {
        std::cout << "@" << sc_core::sc_time_stamp() << " [Consumer] Read: " << in_port.read() << std::endl;
    }
};

// Top Module
class Top : public sc_core::sc_module {
public:
    Producer producer;
    Consumer consumer;
    sc_core::sc_signal<int> sig_data;

    Top(sc_core::sc_module_name name) 
        : sc_core::sc_module(name), producer("producer"), consumer("consumer"), sig_data("sig_data") {
        
        // Bind ports to the signal
        producer.out_port(sig_data);
        consumer.in_port(sig_data);
    }
};

int sc_main(int argc, char* argv[]) {
    Top top("top_module");
    
    std::cout << "Starting Simulation..." << std::endl;
    sc_core::sc_start();
    
    return 0;
}
