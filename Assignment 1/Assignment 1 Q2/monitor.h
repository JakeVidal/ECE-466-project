#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;

SC_MODULE(monitor){
	sc_in_clk CLK;
	sc_in <bool> RST;
	sc_in <float> XIN, YOUT;

	void output(){
	  cout << "Time" << setw(9) << "RST";
	  cout << setw(6) << "XIN" << setw(12) << "YOUT" << endl;

		while(true){
		  cout << setw(7) << sc_time_stamp() << setw(3) << RST.read();
		  cout << setw(3) << XIN.read() << setw(13) << YOUT.read() << endl;

	          wait();
		}
	}

	SC_CTOR(monitor){
		SC_THREAD(output); sensitive << RST << XIN << YOUT; 
		dont_initialize();
	}
};
