#include "systemc.h"
#include <iostream>
#include <iomanip>

SC_MODULE(monitor){
	sc_in_clk CLK;
	sc_in <bool> RST;
	sc_in <float> XIN, YOUT;

	void output(){
		cout << setw(10) << "Time" << setw(2) << "RST"; 
		cout << setw(2) << "XIN" << setw(2) << "YOUT" << endl;

		while(true){
			cout << setw(10) << sc_time_stamp() << setw(2) << RST.read();
			cout << setw(2) << XIN.read() << setw(2) << YOUT.read();

			wait();
		}
	}

	SC_CTOR(monitor){
		SC_THREAD(output); sensitive << RST << XIN << YOUT; 
		dont_initialize();
	}
}