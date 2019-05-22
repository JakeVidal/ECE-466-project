#include "systemc.h"

SC_MODULE(stimulus){
	sc_in_clk CLK;
	sc_out <bool> RST;
	sc_out <float> XIN;

	void generate(){
		RST.write(true); wait(); RST.write(false);
		XIN.write(1); wait();
		XIN.write(0); wait();
	}

	SC_CTOR(stimulus){
		SC_CTHREAD(generate, CLK.pos());
		XIN.initialize(0);
		RST.initialize(false);
	}
};
