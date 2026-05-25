#include <systemc>

SC_MODULE(CounterBlock) {
    sc_core::sc_in<bool> clk{"clk"};
    sc_core::sc_in<bool> rst{"rst"};
    sc_core::sc_out<sc_dt::sc_uint<8>> count{"count"};

    SC_CTOR(CounterBlock) {
        SC_CTHREAD(run, clk.pos());
        reset_signal_is(rst, true);
    }

    void run() {
        count.write(0);
        wait();

        while (true) {
            count.write(count.read() + 1);
            wait();
        }
    }
};

int sc_main(int, char*[]) {
    sc_core::sc_clock clk{"clk", 10, sc_core::SC_NS};
    sc_core::sc_signal<bool> rst{"rst"};
    sc_core::sc_signal<sc_dt::sc_uint<8>> count{"count"};

    CounterBlock dut{"dut"};
    dut.clk(clk);
    dut.rst(rst);
    dut.count(count);

    rst.write(true);
    sc_core::sc_start(20, sc_core::SC_NS);
    rst.write(false);
    sc_core::sc_start(80, sc_core::SC_NS);

    return 0;
}
