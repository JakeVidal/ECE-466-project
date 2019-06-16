#include "systemc.h"
#include "fifo.h"
#include <iostream>
#include <iomanip>

using namespace std;

template <class T> class producer : public sc_module {
public:
    sc_port < fifo_out_if<T> > out;
    sc_in <bool> clk;

    void do_writes() {
        T data = 0;
        while (true) {
            wait();

            if (out->write(data)) {
                cout << "W " << data << " at " << sc_time_stamp() << endl;
                data = (data + 1) % 10;
            }
        }
    }

    SC_CTOR(producer) {
        SC_THREAD(do_writes);
        sensitive << clk.pos();
    }
};