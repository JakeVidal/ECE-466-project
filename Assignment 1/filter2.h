#include "systemc.h"

SC_MODULE(filter2){	
	sc_in_clk CLK;
	sc_in <bool> RST;
	sc_in <float> XIN;
	sc_out <float> YOUT;

	sc_signal <float> Z1_IN, Z2_IN, Z1_OUT, Z2_OUT;

	void inout(){
		Z1_IN.write(XIN.read() - ((0.5*Z1_OUT.read())+(0.25*(XIN.read()+Z2_OUT.read()))));
		Z2_IN.write(Z1_OUT.read());

		YOUT.write(Z2_OUT.read() + ((0.5*Z1_OUT.read())+(0.25*(XIN.read()+Z2_OUT.read()))));
	}

	void update(){
		sc_signal <float> VAL1, VAL2;
		VAL1.write(0);
		VAL2.write(0);	
		Z1_OUT.write(0);
		Z2_OUT.write(0);

		while(true){
			VAL1.write(Z1_IN.read());
			VAL2.write(Z2_IN.read());

			wait();

			Z1_OUT.write(VAL1.read());
			Z2_OUT.write(VAL2.read());
		}
	}

	SC_CTOR(adder){
		SC_METHOD(inout); sensitive << XIN << Z1_OUT << Z2_OUT;
		SC_CTHREAD(update, CLK.pos()); reset_signal_is(RST, true);
	}
};

//might need to add initial values