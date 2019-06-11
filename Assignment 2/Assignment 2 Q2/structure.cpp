#include "systemc.h"
#include "memory.h"
#include "testbench.h"
#include <iostream>
#include <iomanip>

int sc_main(int argc, char* argv[]){
	sc_clock TestClk("CLKTEST", 10, SC_NS, 0.5, 1, SC_NS);
	sc_signal <bool> RST;
	sc_signal <float> XIN, YOUT;

        filter2 DUT("filter2");
	DUT.CLK(TestClk); DUT.RST(RST); DUT.XIN(XIN); DUT.YOUT(YOUT);

	stimulus STIM("stimulus");
	STIM.CLK(TestClk); STIM.RST(RST); STIM.XIN(XIN);

	monitor MON("monitor");
	MON.CLK(TestClk); MON.RST(RST); MON.XIN(XIN); MON.YOUT(YOUT);

	sc_trace_file* TF = sc_create_vcd_trace_file("filter_traces");
	TF->set_time_unit(1, SC_NS);
	sc_trace(TF, RST, "RST");
	sc_trace(TF, XIN, "X");
	sc_trace(TF, YOUT, "Y");

	sc_start(210, SC_NS);
        sc_close_vcd_trace_file(TF);
	return 0;
	
};

int sc_main(int argc, char* argv[])
{
    // Memory module instance:
    mem_ctrl MC("MC");
    
    // Your testbench module(s) instances:
    ...


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

    ...


    // Rest of sc_main ...

    return 0;
}

