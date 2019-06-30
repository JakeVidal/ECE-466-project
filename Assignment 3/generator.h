// Simple constant generator

template <class T> SC_MODULE (DF_Const) {
	sc_fifo_out <T> output;

	void process() {
		while (1) output.write (constant_);
	}

	SC_HAS_PROCESS (DF_Const);
	DF_Const (sc_module_name NAME, const T& CONSTANT) : sc_module (NAME),
	constant_ (CONSTANT) {
		SC_THREAD (process);
	}

	T constant_; // constant value we write to the output
}; 