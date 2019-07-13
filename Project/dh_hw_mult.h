#include "systemc.h"
#include "digit.h"

#ifndef _DH_HW_MULT_H_
#define _DH_HW_MULT_H_ 1

SC_MODULE (dh_hw_mult)
{
  sc_in<bool> hw_mult_enable; 
  sc_in<NN_DIGIT> in_data_1;
  sc_in<NN_DIGIT> in_data_2;
  sc_out<NN_DIGIT> out_data_low;
  sc_out<NN_DIGIT> out_data_high;
  sc_out<bool> hw_mult_done;

  void process_hw_mult();
  
  SC_CTOR (dh_hw_mult)
  {
    SC_THREAD (process_hw_mult);
    sensitive << hw_mult_enable;
  }
  
};

#endif /* end _DH_HW_MULT_H_ */
