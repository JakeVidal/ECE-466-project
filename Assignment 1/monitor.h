#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;

SC_MODULE(monitor){
	sc_in_clk CLK;
	sc_in <bool> RST;
	sc_in <float> XIN, YOUT;

	void output(){
		cout << "Time  RST  XIN  YOUT" << endl; 

		while(true){
			cout << sc_time_stamp() << setw(2) << RST.read();
			cout << setw(2) << XIN.read() << setw(2) << YOUT.read() << endl;

			wait();
		}
	}

	SC_CTOR(monitor){
		SC_THREAD(output); sensitive << RST << XIN << YOUT; 
		dont_initialize();
	}
};
