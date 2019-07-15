#include "systemc.h"
#include "digit.h"

#ifndef _DH_HW_MULT_H_
#define _DH_HW_MULT_H_ 1

SC_MODULE (dh_hw_mult)
{
  sc_in_clk clk;
  sc_in<bool> hw_mult_enable; 
  sc_in<NN_DIGIT> in_data_1;
  sc_in<NN_DIGIT> in_data_2;
  sc_out<NN_DIGIT> out_data_low;
  sc_out<NN_DIGIT> out_data_high;
  sc_out<bool> hw_mult_done;

  //add more interconnection signals here
  sc_signal<NN_DIGIT> b_hh, b_lh, c_hh, c_lh, t, u, a0, a1;
  sc_signal<bool> ld_b, ld_c, ld_u, ld_t, ld_a0, ld_a1;

  //instatiate modules here
  hw_register b_register("b_register");
  hw_register c_register("c_register");
  hw_register u_register("u_register");
  hw_register t_register("t_register");
  hw_register a0_register("a0_register");
  hw_register a1_register("a1_register");

  hw_splitter b_splitter("b_splitter");
  hw_splitter c_splitter("c_splitter");

  hw_multiplier u_multiplier("u_multiplier");
  hw_multiplier t_multiplier("t_multiplier");
  hw_multiplier a0_multiplier("a0_multiplier");
  hw_multiplier a1_multiplier("a1_multiplier");

  hw_adder t_adder("t_adder");
  hw_adder a0_adder("a0_adder");
  hw_adder a1_adder_1("a1_adder_1");
  hw_adder a1_adder_2("a1_adder_2");
  hw_adder a1_adder_3("a1_adder_3");

  hw_multiplexor u_multiplexor("u_multiplexor");
  hw_multiplexor t_multiplexor("t_multiplexor");
  hw_multiplexor a0_multiplexor("a0_multiplexor");
  hw_multiplexor a1_multiplexor_1("a1_multiplexor_1");
  hw_multiplexor a1_multiplexor_2("a1_multiplexor_2");
  hw_multiplexor a1_multiplexor_3("a1_multiplexor_3");

  hw_comparator t_comparator("t_comparator");
  hw_comparator a0_comparator("a0_comparator");

  hw_to_hh t_to_hh("t_to_hh");
  hw_to_hh const_to_hh("const_to_hh");

  hw_hh_extract t_hh_extract("t_hh_extract");

  //define module interconnections here
  
  void process_hw_mult();
  
  SC_CTOR (dh_hw_mult)
  {
    SC_CTHREAD (process_hw_mult, clk.pos());
  }
  
};

#endif /* end _DH_HW_MULT_H_ */
