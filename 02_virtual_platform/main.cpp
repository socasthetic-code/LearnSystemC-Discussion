#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

// 1. RAM Peripheral
class RAM : public sc_core::sc_module {
public:
    tlm_utils::simple_target_socket<RAM> socket;
    SC_HAS_PROCESS(RAM);
    RAM(sc_core::sc_module_name name, unsigned int size_bytes) 
        : sc_core::sc_module(name), size(size_bytes) {
        memory = new unsigned char[size];
        memset(memory, 0, size);
        socket.register_b_transport(this, &RAM::b_transport);
    }
    ~RAM() { delete[] memory; }
private:
    unsigned char* memory;
    unsigned int size;
    void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
        if (trans.get_address() + trans.get_data_length() > size) {
            trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
            return;
        }
        if (trans.get_command() == tlm::TLM_READ_COMMAND)
            memcpy(trans.get_data_ptr(), &memory[trans.get_address()], trans.get_data_length());
        else if (trans.get_command() == tlm::TLM_WRITE_COMMAND)
            memcpy(&memory[trans.get_address()], trans.get_data_ptr(), trans.get_data_length());
        
        delay += sc_core::sc_time(10, sc_core::SC_NS);
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
};

// 2. Timer Peripheral
class Timer : public sc_core::sc_module {
public:
    tlm_utils::simple_target_socket<Timer> socket;
    SC_HAS_PROCESS(Timer);
    Timer(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        socket.register_b_transport(this, &Timer::b_transport);
        SC_THREAD(timer_thread);
    }
private:
    bool running = false;
    unsigned int counter = 0;
    sc_core::sc_event start_event;
    void timer_thread() {
        while(true) {
            if (!running) wait(start_event);
            wait(1, sc_core::SC_US);
            if (running) counter++;
        }
    }
    void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
        if (trans.get_command() == tlm::TLM_WRITE_COMMAND && trans.get_address() == 0x00) {
            running = (*trans.get_data_ptr() != 0);
            if (running) start_event.notify();
        } else if (trans.get_command() == tlm::TLM_READ_COMMAND && trans.get_address() == 0x04) {
            memcpy(trans.get_data_ptr(), &counter, sizeof(counter));
        }
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
};

// 3. Router
class Router : public sc_core::sc_module {
public:
    tlm_utils::simple_target_socket<Router> target_socket;
    tlm_utils::simple_initiator_socket<Router> init_socket[2];
    SC_HAS_PROCESS(Router);
    Router(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        target_socket.register_b_transport(this, &Router::b_transport);
    }
private:
    void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
        sc_dt::uint64 address = trans.get_address();
        if (address >= 0x00000000 && address <= 0x0003FFFF) { // RAM
            init_socket[0]->b_transport(trans, delay);
        } else if (address >= 0x40000000 && address <= 0x40000FFF) { // Timer
            trans.set_address(address - 0x40000000);
            init_socket[1]->b_transport(trans, delay);
            trans.set_address(address);
        } else {
            trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
        }
    }
};

// 4. CPU (Initiator)
class CPU : public sc_core::sc_module {
public:
    tlm_utils::simple_initiator_socket<CPU> socket;
    SC_HAS_PROCESS(CPU);
    CPU(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        SC_THREAD(execute_firmware);
    }
private:
    void execute_firmware() {
        tlm::tlm_generic_payload trans;
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        unsigned int data;

        std::cout << "[CPU] Booting up..." << std::endl;

        // Write '1' to Timer Control
        data = 1;
        trans.set_command(tlm::TLM_WRITE_COMMAND);
        trans.set_address(0x40000000);
        trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        trans.set_data_length(4);
        socket->b_transport(trans, delay);
        std::cout << "[CPU] Started Timer." << std::endl;

        wait(5, sc_core::SC_US);

        // Read Timer Counter
        trans.set_command(tlm::TLM_READ_COMMAND);
        trans.set_address(0x40000004);
        socket->b_transport(trans, delay);
        std::cout << "[CPU] Timer Counter is " << data << " (Expected ~5)" << std::endl;

        sc_core::sc_stop();
    }
};

// 5. Top Level
int sc_main(int argc, char* argv[]) {
    CPU cpu("cpu");
    Router router("router");
    RAM ram("ram", 0x40000);
    Timer timer("timer");

    cpu.socket.bind(router.target_socket);
    router.init_socket[0].bind(ram.socket);
    router.init_socket[1].bind(timer.socket);

    sc_core::sc_start();
    return 0;
}
