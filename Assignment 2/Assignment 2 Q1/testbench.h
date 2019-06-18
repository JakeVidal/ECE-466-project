#define WTBYT 0
#define RDBYT 1
#define WTBLK 2
#define RDBLK 3

#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;
	
SC_MODULE(testbench) {

	sc_inout <sc_lv<8> > data; // Bidirectional port of logic-vector type
	sc_out < sc_uint<8> > addr;
	sc_out < sc_uint<2> > comm;
	sc_in <bool> reset;
	sc_out <bool> new_comm; // Input port signaling “start”
	sc_in <bool> complete; // Output port signaling “done”
 
	sc_in_clk clk;

	void test_process() {
		sc_lv <8> data_s;  
		while (true) {
			if (reset.read() == true) new_comm.write(false);
			else {
			  
			cout << "-----------------------------------------------------------------" << endl;
			cout << " TEST RDBYT COMMAND ON UNPOPULATED ADDRESS 0:" << endl;
			addr.write(0x00); // set-up for RDBYT command
			comm.write(RDBYT);
			wait();
			new_comm.write(true); // send command to memory
			while (complete.read() == false) {
				wait();
			}
			data_s = data.read();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBYT, address = 0"
			<< ", data = " << data_s << endl;
			new_comm.write(false);
			wait();
			wait();
			data_s = data.read();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench check bus release"
			<< ", data = " << data_s << endl;
			
			cout << "-----------------------------------------------------------------" << endl;
			cout << " TEST WTBYT COMMAND ON UNPOPULATED ADDRESS 0:" << endl;
			data.write(0xAA); // set-up for WTBYT command
			addr.write(0x00);
			comm.write(WTBYT);
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench WTBYT, address = 0, data = 10101010" << endl;
			new_comm.write(true); // send command to memory
			while (complete.read() == false) {
				wait();
			}
			data.write(Z);
			new_comm.write(false);
			wait();
			
			cout << "-----------------------------------------------------------------" << endl;
			cout << " TEST RDBYT COMMAND ON POPULATED ADDRESS 0:" << endl;
			addr.write(0x00); // set-up for RDBYT command
			comm.write(RDBYT);
			wait();
			new_comm.write(true); // send command to memory
			while (complete.read() == false) {
				wait();
			}
			data_s = data.read();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBYT, address = 0"
			<< ", data = " << data_s << endl;
			new_comm.write(false);
			wait();
			wait();
			data_s = data.read();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench check bus release"
			<< ", data = " << data_s << endl;
			
			cout << "-----------------------------------------------------------------" << endl;
			cout << " TEST RDBLK COMMAND UNPOPULATED ADDRESSES 15, 16, 17, 18:" << endl;
			addr.write(0x0F); // set-up for RDBLK command
			comm.write(RDBLK);
			wait();
			new_comm.write(true); // send command to memory
			wait(); wait(); wait();
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-0, address = 15"
			<< ", data = " << data_s << endl;
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-1, address = 16"
			<< ", data = " << data_s << endl;
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-2, address = 17"
			<< ", data = " << data_s << endl;
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-3, address = 18"
			<< ", data = " << data_s << endl;
			while (complete.read() == false) {
				wait();
			}
			new_comm.write(false);
			wait();
			}
			wait();
			data_s = data.read();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench check bus release"
			<< ", data = " << data_s << endl;
			
			cout << "-----------------------------------------------------------------" << endl;
			cout << " TEST WTBLK COMMAND UNPOPULATED ADDRESSES 15, 16, 17, 18:" << endl;
			data.write(0xFF); // set-up for WTBLK command
			addr.write(0x0F);
			comm.write(WTBLK);
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench WTBLK-0, address = 15, data = 11111111" << endl;
			wait();
			new_comm.write(true);
			wait();
			data.write(0xEE);
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench WTBLK-1, address = 16, data = 11101110" << endl;
			wait();
			data.write(0xCC);
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench WTBLK-2, address = 17, data = 11001100" << endl;
			wait();
			data.write(0x88);
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench WTBLK-3, address = 18, data = 10001000" << endl;
			while (complete.read() == false) {
				wait();
			}
			data.write(Z);
			new_comm.write(false);
			wait();
			
			cout << "-----------------------------------------------------------------" << endl;
			cout << " TEST RDBLK COMMAND POPULATED ADDRESSES 15, 16, 17, 18:" << endl;
			addr.write(0x0F); // set-up for RDBLK command
			comm.write(RDBLK);
			wait();
			new_comm.write(true); // send command to memory
			wait(); wait(); wait();
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-0, address = 15"
			<< ", data = " << data_s << endl;
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-1, address = 16"
			<< ", data = " << data_s << endl;
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-2, address = 17"
			<< ", data = " << data_s << endl;
			data_s = data.read();
			wait();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench RDBLK-3, address = 18"
			<< ", data = " << data_s << endl;
			while (complete.read() == false) {
				wait();
			}
			new_comm.write(false);
			wait();
			wait();
			data_s = data.read();
			cout << "@" << setw(6) << sc_time_stamp() << ": testbench check bus release"
			<< ", data = " << data_s << endl;
			
			wait();
			data.write(Z);
		}
	}
	
	SC_CTOR(testbench) { 
		SC_CTHREAD(test_process, clk.pos()); 
	}
};