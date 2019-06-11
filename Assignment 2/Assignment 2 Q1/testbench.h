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

    sc_inout <sc_lv<8> > data; // Bidirectional port of logic-vector type
    sc_in < sc_uint<8> > addr;
    sc_in < sc_uint<2> > comm;
    sc_in <bool> new_comm; // Input port signaling “start”
    sc_out <bool> complete; // Output port signaling “done”
 
    sc_in_clk clk;

    void test_process() {
	sc_lv <8> data_s;  
	while (true) {
	    if (reset.read() == true) new_comm.write(false);
	    else {
		data.write(0xFF); // set-up for WTBYT command
		addr.write(0xFF);
		comm.write(WTBYT);
		wait();
		new_comm.write(true); // send command to memory
		while (complete.read() == false) {
		    wait();
		}
		data.write(Z);
		new_comm.write(false);
		wait();
		
		addr.write(0xFF); // set-up for RDBYT command
		comm.write(RDBYT);
		wait();
		new_comm.write(true); // send command to memory
		while (complete.read() == false) {
		    wait();
		}
		data_s = data.read();
		new_comm.write(false);
		wait();
		
		data.write(0xEE); // set-up for WTBLK command
		addr.write(0x00);
		comm.write(WTBLK);
		wait();
		new_comm.write(true);
		wait();
		data.write(0xDD);
		wait();
		data.write(0xCC);
		wait();
		data.write(0xBB);
		while (complete.read() == false) {
		    wait();
		}
		data.write(Z);
		new_comm.write(false);
		wait();
		
		addr.write(0x00); // set-up for RDBLK command
		comm.write(RDBLK);
		wait();
		new_comm.write(true); // send command to memory
		wait();
		data_s = data.read();
		wait();
		data_s = data.read();
		wait();
		data_s = data.read();
		wait();
		data_s = data.read();
		while (complete.read() == false) {
		    wait();
		}
		new_comm.write(false);
		wait();
	    }
	}
    }
    
    SC_CTOR(testbench) { 
	SC_CTHREAD(test_process, clk.pos()); 
    }
};