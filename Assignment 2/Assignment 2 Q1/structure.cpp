#include "systemc.h"
#include "memory.h"
#include "testbench.h"
#include <iostream>
#include <iomanip>

int sc_main(int argc, char* argv[])
{
    mem_ctrl MC("MC");
    testbench TB("TB");
    sc_clock TestClk("CLKTEST", 10, SC_NS, 0.5, 1, SC_NS);

    // Internal signals:
    sc_signal <bool> reset, new_comm, complete;
    sc_signal < sc_uint<2> > comm;
    sc_signal < sc_uint<8> > addr;
    sc_signal_rv <8> data;
    // _rv needed because of multiple drivers
  
    // Interconnects:
    MC.clk(clk);
    MC.reset(reset);
    MC.data(data);
    MC.addr(addr);
    MC.comm(comm);
    MC.new_comm(new_comm);
    MC.complete(complete);

    TB.clk(clk);
    TB.reset(reset);
    TB.data(data);
    TB.addr(addr);
    TB.comm(comm);
    TB.new_comm(new_comm);
    TB.complete(complete);

    sc_trace_file* TF = sc_create_vcd_trace_file("memory_traces");
    TF->set_time_unit(1, SC_NS);
    sc_trace(TF, clk, "clk");
    sc_trace(TF, reset, "reset");
    sc_trace(TF, data, "data");
    sc_trace(TF, addr, "addr");
    sc_trace(TF, comm, "comm");
    sc_trace(TF, new_comm, "new_comm");
    sc_trace(TF, complete, "complete");

    sc_start(210, SC_NS);
    sc_close_vcd_trace_file(TF);

    return 0;
}

