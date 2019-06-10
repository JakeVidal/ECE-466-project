#define WTBYT 0
#define RDBYT 1
#define WTBLK 2
#define RDBLK 3

#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;

static sc_logic Z[8] = {SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z,
		        SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z};
			
SC_MODULE(testbench) {
    // Ports
    sc_inout <sc_lv<8> > data; // Bidirectional port of logic-vector type
    sc_in < sc_uint<8> > addr;
    sc_in < sc_uint<2> > comm;
    sc_in <bool> new_comm; // Input port signaling “start”
    sc_out <bool> complete; // Output port signaling “done”
    
    sc_in_clk clk;
    sc_in <bool> reset;

    void test_process() {
	sc_lv <8> data_s;  
	while (true) {
	    if (reset.read() == true) new_comm.write(false);
	    else {
		data.write(0xFF); //set-up for command
		addr.write(0xFF);
		comm.write(RDBYT);
		new_comm.write(true); //send command to memory
		while (complete.read() == false) {
		    if (reset.read() == true) break;
		    wait();
		}
		data_s = data.read(); //read result
		new_comm.write(false);
	    }
	}
    }
    
    SC_CTOR(testbench) { 
	SC_CTHREAD(test_process, clk.pos()); 
    }
};