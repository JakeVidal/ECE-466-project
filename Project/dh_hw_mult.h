#include "systemc.h"
#include "digit.h"
#include "modules.h"

#ifndef _DH_HW_MULT_H_
#define _DH_HW_MULT_H_ 1

SC_MODULE (dh_hw_mult)
{
  //port definitions
  sc_in_clk clk;
  sc_in<bool> hw_mult_enable; 
  sc_in<NN_DIGIT> in_data_1;
  sc_in<NN_DIGIT> in_data_2;
  sc_out<NN_DIGIT> out_data_low;
  sc_out<NN_DIGIT> out_data_high;
  sc_out<bool> hw_mult_done;

  //interconnection signals
  sc_signal<NN_DIGIT> b_hh, b_lh, c_hh, c_lh, b, c, t, u1, u2, a0, a1;
  sc_signal<NN_DIGIT> t_mult;
  sc_signal<NN_DIGIT> a0_mult, a0_add_u2;
  sc_signal<NN_DIGIT> a1_mult, a1_add_1_to_hh, a1_mux_out_1, a1_add_1, a1_mux_out_2, a1_t_hh, a1_add_t_hh;
  sc_signal<bool> ld_b, ld_c, ld_a0, ld_a1, lt_1, lt_2, a1_mux_1_ctrl, a1_mux_2_ctrl;
  sc_signal<UINT4> hh_1, const_1;
 
  //multiplier thread
  void process_hw_mult();
  
  //module instatiation
  hw_register b_register, c_register, a0_register, a1_register;
  hw_splitter b_splitter, c_splitter;
  hw_multiplier u_multiplier, t_multiplier, a0_multiplier, a1_multiplier;
  hw_adder t_adder, a0_adder, a1_adder_1, a1_adder_2, a1_adder_3;
  hw_multiplexor a1_multiplexor_1, a1_multiplexor_2;
  hw_comparator t_comparator, a0_comparator;
  hw_to_hh t_to_hh;
  hw_hh_extract t_hh_extract;
  
  //multiplier constructor
  SC_CTOR (dh_hw_mult):
  b_register("b_register"), c_register("c_register"), a0_register("a0_register"), a1_register("a1_register"),
  b_splitter("b_splitter"), c_splitter("c_splitter"), u_multiplier("u_multiplier"), t_multiplier("t_multiplier"), a0_multiplier("a0_multiplier"), a1_multiplier("a1_multiplier"),
  t_adder("t_adder"), a0_adder("a0_adder"), a1_adder_1("a1_adder_1"), a1_adder_2("a1_adder_2"), a1_adder_3("a1_adder_3"),
  a1_multiplexor_1("a1_multiplexor_1"), a1_multiplexor_2("a1_multiplexor_2"),
  t_comparator("t_comparator"), a0_comparator("a0_comparator"), t_to_hh("t_to_hh"),  t_hh_extract("t_hh_extract")
  {
    //initialize constants
    hh_1.write(0x10000);
    const_1.write(0x1);

    //define register interconnection
    b_register.clk(clk); b_register.in_data(in_data_1); b_register.load_data(ld_b); b_register.out_data(b);
    c_register.clk(clk); c_register.in_data(in_data_2); c_register.load_data(ld_c); c_register.out_data(c);
    a0_register.clk(clk); a0_register.in_data(a0_add_u2); a0_register.load_data(ld_a0); a0_register.out_data(a0);
    a1_register.clk(clk); a1_register.in_data(a1_add_t_hh); a1_register.load_data(ld_a1); a1_register.out_data(a1);
    
    //define splitter interconnection
    b_splitter.in_data(b); b_splitter.out_data_high(b_hh); b_splitter.out_data_low(b_lh);
    c_splitter.in_data(c); c_splitter.out_data_high(c_hh); c_splitter.out_data_low(c_lh); 
    
    //define multiplier interconnection
    u_multiplier.in_data_1(b_hh); u_multiplier.in_data_2(c_lh); u_multiplier.out_data(u1);
    t_multiplier.in_data_1(b_lh); t_multiplier.in_data_2(c_hh); t_multiplier.out_data(t_mult);
    a0_multiplier.in_data_1(b_lh); a0_multiplier.in_data_2(c_lh); a0_multiplier.out_data(a0_mult);
    a1_multiplier.in_data_1(b_hh); a1_multiplier.in_data_2(c_hh); a1_multiplier.out_data(a1_mult);
    
    //define adder interconnection
    t_adder.in_data_1(t_mult); t_adder.in_data_2(u1); t_adder.out_data(t);
    a0_adder.in_data_1(a0_mult); a0_adder.in_data_2(u2); a0_adder.out_data(a0_add_u2);
    a1_adder_1.in_data_1(a1_mult); a1_adder_1.in_data_2(hh_1); a1_adder_1.out_data(a1_add_1_to_hh);
    a1_adder_2.in_data_1(a1_mux_out_1); a1_adder_2.in_data_2(const_1); a1_adder_2.out_data(a1_add_1);
    a1_adder_3.in_data_1(a1_mux_out_2); a1_adder_3.in_data_2(a1_t_hh); a1_adder_3.out_data(a1_add_t_hh);
    
    //define multiplexor interconnection
    a1_multiplexor_1.in_data_1(a1_mult); a1_multiplexor_1.in_data_2(a1_add_1_to_hh); a1_multiplexor_1.control(a1_mux_1_ctrl); a1_multiplexor_1.out_data(a1_mux_out_1);
    a1_multiplexor_2.in_data_1(a1_mux_out_1); a1_multiplexor_2.in_data_2(a1_add_1); a1_multiplexor_2.control(a1_mux_2_ctrl); a1_multiplexor_2.out_data(a1_mux_out_2);
    
    //define compartor interconnection
    t_comparator.in_data_reference(u1); t_comparator.in_data_comparison(t); t_comparator.less_than_signal(lt_1);
    a0_comparator.in_data_reference(u2); a0_comparator.in_data_comparison(a0); a0_comparator.less_than_signal(lt_2);
    
    //define misc interconnections
    t_to_hh.in_data(t); t_to_hh.out_data(u2);
    t_hh_extract.in_data(t); t_hh_extract.out_data(a1_t_hh);
    
    //create multiplier thread
    SC_CTHREAD (process_hw_mult, clk.pos());
  }
};

#endif /* end _DH_HW_MULT_H_ */
