#include <systemc>
#include <iostream>

// This is a tiny SystemC-shaped stand-in for the UVM-SystemC lessons.
// Replace this with real uvm::uvm_component code once your UVM-SystemC
// installation is wired into CMake.
class MiniVerificationComponent : public sc_core::sc_module {
public:
    SC_HAS_PROCESS(MiniVerificationComponent);

    explicit MiniVerificationComponent(sc_core::sc_module_name name)
        : sc_core::sc_module(name) {
        SC_THREAD(run_phase_like_thread);
    }

private:
    void run_phase_like_thread() {
        SC_REPORT_INFO(name(), "raise objection: stimulus is active");
        wait(10, sc_core::SC_NS);
        SC_REPORT_INFO(name(), "drop objection: stimulus is complete");
    }
};

int sc_main(int, char*[]) {
    MiniVerificationComponent test("uvm_style_test");
    sc_core::sc_start();
    return 0;
}
