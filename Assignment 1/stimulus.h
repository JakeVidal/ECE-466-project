#include "systemc.h"

SC_MODULE(stimulus){
	sc_in_clk CLK;
	sc_out <bool> RST;
	sc_out <float> XIN;

	void generate(){
		RST.write(true); wait(); RST.write(false);
		IN.write(1); wait();
		IN.write(0); wait();
		sc_stop();
	}

	SC_CTOR(){
		SC_CTHREAD(generate, CLK.pos());
		IN.initialize(0);
		RST.initialize(false);
	}
}