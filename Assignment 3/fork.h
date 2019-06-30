// This module forks a dataflow stream

template <class T> SC_MODULE (DF_Fork) {
	sc_fifo_in <T> input;
	sc_fifo_out <T> output1, output2;

	void process() {
		while(1) {
			T value = input.read();
			output1.write (value);
			output2.write (value);
		}
	}

	SC_CTOR (DF_Fork) {
		SC_THREAD (process);
	}
};