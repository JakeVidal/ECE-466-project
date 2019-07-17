#include "systemc.h"
#include "digit.h"
#include "modules.h"


void hw_register::run_hw_register()
{
	while(true)
	{
		wait();
		
		if (load_data.read() == 1)
		{	
			out_data.write(in_data.read());
		}
	}
}

void hw_splitter::run_hw_splitter()
{
	out_data_high.write(HIGH_HALF(in_data.read()));
	out_data_low.write(LOW_HALF(in_data.read()));
}

void hw_multiplier::run_hw_multiplier()
{
	out_data.write(in_data_1.read() * in_data_2.read());
}

void hw_adder::run_hw_adder()
{
	out_data.write(in_data_1.read() + in_data_2.read());
}

void hw_multiplexor::run_hw_multiplexor()
{
	if (control.read() == 0)
	{
		out_data.write(in_data_1.read());
	}
	else
	{
		out_data.write(in_data_2.read());
	}
}

void hw_to_hh::run_hw_to_hh()
{
	out_data.write(TO_HIGH_HALF(in_data.read()));
}

void hw_hh_extract::run_hw_hh_extract()
{
	out_data.write(HIGH_HALF(in_data.read()));
}

void hw_comparator::run_hw_comparator()
{
	if (in_data_comparison.read() < in_data_reference.read())
	{
		less_than_signal.write(1);
	}
	else
	{
		less_than_signal.write(0);
	}
}
