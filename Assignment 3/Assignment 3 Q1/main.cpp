#include "systemc.h"
#include "adder.h"
#include "fork.h"
#include "generator.h"
#include "printer.h"
#include "hw_fifo.h"
#include "read_adapter.h"

int sc_main (int argc, char* argv[]) {
	DF_Const<int> constant ("constant", 1); // constant = 1
	HW_Adder<int> adder ("adder");
        FIFO_READ_HS<int> adapter ("adapter");
	DF_Fork<int> fork("fork");
	DF_Printer<int> printer ("printer", 10); // 10 interations

	sc_fifo<int> const_out ("const_out", 1); // FIFO of size 1
	hw_fifo<int> adder_out ("adder_out", 1); // FIFO of size 1
	sc_fifo<int> printer_in ("printer_in", 1); // FIFO of size 1
	sc_fifo<int> feedback ("feedback", 1); // FIFO of size 1
	feedback.write (40); // do not forget about initialization!

	sc_clock TestClk ("Testclock", 10, SC_NS, 0.5, 1, SC_NS);

	sc_signal<int> add_data, fifo_data;
	sc_signal<bool> add_valid, fifo_valid, fifo_ready, adapter_ready;

	constant.output(const_out); printer.input(printer_in);

	adder.input1(const_out); adder.input2(feedback); 
	adder.clock(TestClk); adder.data(add_data); 
	adder.valid(add_valid); adder.ready(fifo_ready);

	adder_out.clk(TestClk); adder_out.data_in(add_data);
	adder_out.valid_in(add_valid); adder_out.ready_in(adapter_ready);
	adder_out.data_out(fifo_data); adder_out.valid_out(fifo_valid);
	adder_out.ready_out(fifo_ready);

	adapter.clock(TestClk); adapter.data(fifo_data);
	adapter.valid(fifo_valid); adapter.ready(adapter_ready);

	fork.input (adapter); fork.output1 (feedback); fork.output2 (printer_in);

	// Start simulation without time limit
	// The printer module is responsible for stopping the simulation
	sc_start ();
	return 0;
}
