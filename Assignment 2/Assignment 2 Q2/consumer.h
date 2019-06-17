#include "systemc.h"
#include "fifo_if.h"
#include <iostream>
#include <iomanip>
using namespace std;

template <class T> class consumer : public sc_module {
public:
    sc_port < fifo_in_if<T> > in;
    sc_in <bool> clk;
  
    void do_reads() {
        T data;
        while (true) {
            wait();

            if (in->read(data)) {
		cout << "@" << setw(6) << sc_time_stamp() << " write: X " << "read: " << data << endl;
            }
        }
    }

    SC_CTOR(consumer) {
        SC_THREAD(do_reads);
        sensitive << clk.pos();
    }
};