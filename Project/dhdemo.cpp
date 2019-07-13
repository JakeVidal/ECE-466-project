#include "systemc.h"
#include "digit.h"
#include "dh_sw.h"
#include "dh_hw_mult.h"

int sc_main(int argc , char *argv[])
{

	sc_signal <bool> enable, done;
	sc_signal <NN_DIGIT> operand1, operand2, result1, result2;
	
	enable.write(false);
	done.write(false);
	
	dh_sw DH_SW("DH_Software");
	DH_SW.out_data_1 (operand1);		// operand1 to hardware
	DH_SW.out_data_2 (operand2);		// operand2 to hardware
	DH_SW.in_data_low (result1);		// result1 from hardware
	DH_SW.in_data_high (result2);		// result2 from hardware
	DH_SW.hw_mult_enable (enable);		// enable hardware
	DH_SW.hw_mult_done (done);		// hardware done
	
	
	dh_hw_mult DH_HW_MULT("DH_Hardware_Multiplier");
	DH_HW_MULT.in_data_1 (operand1);	// operand1 from software
	DH_HW_MULT.in_data_2 (operand2);	// operand2 from software
	DH_HW_MULT.out_data_low (result1);	// result1 to software
	DH_HW_MULT.out_data_high (result2);	// result2 to software
	DH_HW_MULT.hw_mult_enable (enable);	// enable hardware
	DH_HW_MULT.hw_mult_done (done);		// hardware done

	sc_start();

	return(0);
}
