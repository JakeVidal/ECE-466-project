#include "systemc.h"
#include "filter.h"
#include "stimulus.h"
#include "monitor.h"
#include <iostream>

int sc_main(int argc, char* argv[]){
	sc_clock TestClk("CLKTEST", 10, SC_NS, 0.5, 1, SC_NS);
	sc_signal <bool> RST;
	sc_signal <float> XIN, YOUT;

	filter DUT("filter");
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
