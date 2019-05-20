#include "systemc.h"

SC_MODULE(adder){	
	sc_in <float> NUM1, NUM2;
	sc_out <float> OUT;

	void add(){
		OUT.write(NUM1.read() + NUM2.read());
	}

	SC_CTOR(adder){
		SC_METHOD(add); sensitive << NUM1 << NUM2;
	}
}

SC_MODULE(multiplier){
	sc_in <float> NUM1, NUM2;
	sc_out <float> OUT;

	void multiply(){
		OUT.write(NUM1.read() * NUM2.read());
	}

	SC_CTOR(multiplier){
		SC_METHOD(multiply); sensitive << NUM1 << NUM2;
	}
}

SC_MODULE(clkregister){
	sc_in_clk CLK;
	sc_in <bool> RST;
	sc_in <float> IN;
	sc_out <float> OUT;

	void update(){
		sc_signal <float> VAL = 0;
		OUT.write(0);

		while(true){
			VAL.write(IN.read());

			wait();

			OUT.write(VAL.read());
		}
	}

	SC_CTOR(clkregister){
		SC_CTHREAD(update, CLK.pos()); reset_signal_is(RST, true);
	}
}
