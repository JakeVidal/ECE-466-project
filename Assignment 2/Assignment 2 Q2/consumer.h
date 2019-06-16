#include "systemc.h"
#include "fifo.h"
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
                cout << "R " << data << " at " << sc_time_stamp() << endl;
            }
        }
    }

    SC_CTOR(consumer) {
        SC_THREAD(do_reads);
        sensitive << clk.pos();
    }
};