#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

// A simple Initiator (e.g. CPU)
class Initiator : public sc_core::sc_module {
public:
    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_HAS_PROCESS(Initiator);

    Initiator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        SC_THREAD(run);
    }

private:
    void run() {
        tlm::tlm_generic_payload trans;
        sc_core::sc_time delay = sc_core::sc_time(10, sc_core::SC_NS);
        unsigned int data = 42;

        trans.set_command(tlm::TLM_WRITE_COMMAND);
        trans.set_address(0x1000);
        trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        trans.set_data_length(4);
        trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

        std::cout << "@" << sc_core::sc_time_stamp() << " [Initiator] Sending Write to 0x1000 with data " << data << std::endl;
        
        // Blocking transport call
        socket->b_transport(trans, delay);

        if (trans.is_response_error()) {
            std::cerr << "Transaction returned with error!" << std::endl;
        } else {
            std::cout << "@" << sc_core::sc_time_stamp() << " [Initiator] Transaction complete. Delay accumulated: " << delay << std::endl;
        }
    }
};

// A simple Target (e.g. Memory)
class Target : public sc_core::sc_module {
public:
    tlm_utils::simple_target_socket<Target> socket;

    SC_HAS_PROCESS(Target);

    Target(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        socket.register_b_transport(this, &Target::b_transport);
    }

private:
    void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
        std::cout << "@" << sc_core::sc_time_stamp() << " [Target] Received b_transport request." << std::endl;
        
        // Process the transaction
        if (trans.get_command() == tlm::TLM_WRITE_COMMAND) {
            unsigned int* data = reinterpret_cast<unsigned int*>(trans.get_data_ptr());
            std::cout << "@" << sc_core::sc_time_stamp() << " [Target] Wrote data: " << *data << " to address: 0x" << std::hex << trans.get_address() << std::dec << std::endl;
        }

        // Add 20ns to the delay to model memory access time
        delay += sc_core::sc_time(20, sc_core::SC_NS);
        
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
};

int sc_main(int argc, char* argv[]) {
    Initiator init("initiator");
    Target target("target");

    // Bind the sockets
    init.socket.bind(target.socket);

    std::cout << "Starting Simulation..." << std::endl;
    sc_core::sc_start();

    return 0;
}
