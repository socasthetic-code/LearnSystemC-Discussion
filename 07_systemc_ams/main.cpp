#include <systemc-ams>
#include <iostream>
#include <cmath>

// A TDF (Timed Data Flow) Module generating a Sine Wave
SCA_TDF_MODULE(SineGenerator) {
    sca_tdf::sca_out<double> out_val; // TDF Output Port

    double amplitude;
    double frequency;

    SCA_CTOR(SineGenerator) 
        : amplitude(1.0), frequency(1000.0) // 1 kHz sine wave
    {}

    // Set the attributes of the TDF node (like timestep)
    void set_attributes() {
        set_timestep(10, sc_core::SC_US); // 10us per sample
    }

    // Processing function called every timestep
    void processing() {
        double t = get_time().to_seconds();
        double val = amplitude * std::sin(2.0 * M_PI * frequency * t);
        out_val.write(val);
    }
};

// A TDF Sink to consume and print the value
SCA_TDF_MODULE(Monitor) {
    sca_tdf::sca_in<double> in_val;

    SCA_CTOR(Monitor) {}

    void set_attributes() {
        // Inherits timestep from the connected signal automatically
    }

    void processing() {
        std::cout << "@" << get_time() << " : " << in_val.read() << std::endl;
    }
};

int sc_main(int argc, char* argv[]) {
    // TDF Signal to connect the modules
    sca_tdf::sca_signal<double> sig_sine;

    // Instantiate modules
    SineGenerator src("sine_src");
    Monitor mon("monitor");

    // Connect ports
    src.out_val(sig_sine);
    mon.in_val(sig_sine);

    std::cout << "Starting SystemC AMS Simulation for 100us..." << std::endl;
    
    // Run simulation for 100 microseconds
    sc_core::sc_start(100, sc_core::SC_US);

    return 0;
}
