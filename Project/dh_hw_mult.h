#include "systemc.h"
#include "digit.h"
#include "modules.h"

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

  //create interconnection signals here
  sc_signal<NN_DIGIT> b_hh, b_lh, c_hh, c_lh, b, c, t, u, a0, a1;
  sc_signal<NN_DIGIT> u_mult, u_mux_t_to_hh, u_mux_out;
  sc_signal<NN_DIGIT> t_mult, t_add_u, t_mux_out;
  sc_signal<NN_DIGIT> a0_mult, a0_add_u, a0_mux_out;
  sc_signal<NN_DIGIT> a1_mult, a1_add_1_to_hh, a1_mux_out_1, a1_add_1, a1_mux_out_2, a1_t_hh, a1_add_t_hh, a1_mux_out_3;
  sc_signal<bool> ld_b, ld_c, ld_u, ld_t, ld_a0, ld_a1, lt_1, lt_2, u_mux_ctrl, t_mux_ctrl, a0_mux_ctrl, a1_mux_1_ctrl, a1_mux_2_ctrl, a1_mux_3_ctrl;
  sc_signal<UINT4> hh_1, const_1;
  
  void process_hw_mult();
  
  hw_register b_register, c_register, u_register, t_register, a0_register, a1_register;
  hw_splitter b_splitter, c_splitter;
  hw_multiplier u_multiplier, t_multiplier, a0_multiplier, a1_multiplier;
  hw_adder t_adder, a0_adder, a1_adder_1, a1_adder_2, a1_adder_3;
  hw_multiplexor u_multiplexor, t_multiplexor, a0_multiplexor, a1_multiplexor_1, a1_multiplexor_2, a1_multiplexor_3;
  hw_comparator t_comparator, a0_comparator;
  hw_to_hh t_to_hh;
  hw_hh_extract t_hh_extract;
  
  SC_CTOR (dh_hw_mult):
  b_register("b_register"), c_register("c_register"), u_register("u_register"), t_register("t_register"), a0_register("a0_register"), a1_register("a1_register"),
  b_splitter("b_splitter"), c_splitter("c_splitter"), u_multiplier("u_multiplier"), t_multiplier("t_multiplier"), a0_multiplier("a0_multiplier"), a1_multiplier("a1_multiplier"),
  t_adder("t_adder"), a0_adder("a0_adder"), a1_adder_1("a1_adder_1"), a1_adder_2("a1_adder_2"), a1_adder_3("a1_adder_3"), u_multiplexor("u_multiplexor"),
  t_multiplexor("t_multiplexor"), a0_multiplexor("a0_multiplexor"), a1_multiplexor_1("a1_multiplexor_1"), a1_multiplexor_2("a1_multiplexor_2"), a1_multiplexor_3("a1_multiplexor_3"),
  t_comparator("t_comparator"), a0_comparator("a0_comparator"), t_to_hh("t_to_hh"),  t_hh_extract("t_hh_extract")
  {
    hh_1.write(0x10000);
    const_1.write(0x1);

    //define module interconnections here
    b_register.clk(clk); b_register.in_data(in_data_1); b_register.load_data(ld_b); b_register.out_data(b);
    c_register.clk(clk); c_register.in_data(in_data_2); c_register.load_data(ld_c); c_register.out_data(c);
    u_register.clk(clk); u_register.in_data(u_mux_out); u_register.load_data(ld_u); u_register.out_data(u);
    t_register.clk(clk); t_register.in_data(t_mux_out); t_register.load_data(ld_t); t_register.out_data(t);
    a0_register.clk(clk); a0_register.in_data(a0_mux_out); a0_register.load_data(ld_a0); a0_register.out_data(a0);
    a1_register.clk(clk); a1_register.in_data(a1_mux_out_3); a1_register.load_data(ld_a1); a1_register.out_data(a1);
    
    b_splitter.in_data(b); b_splitter.out_data_high(b_hh); b_splitter.out_data_low(b_lh);
    c_splitter.in_data(c); c_splitter.out_data_high(c_hh); c_splitter.out_data_low(c_lh); 
    
    u_multiplier.in_data_1(b_hh); u_multiplier.in_data_2(c_lh); u_multiplier.out_data(u_mult);
    t_multiplier.in_data_1(b_lh); t_multiplier.in_data_2(c_hh); t_multiplier.out_data(t_mult);
    a0_multiplier.in_data_1(b_lh); a0_multiplier.in_data_2(c_lh); a0_multiplier.out_data(a0_mult);
    a1_multiplier.in_data_1(b_hh); a1_multiplier.in_data_2(c_hh); a1_multiplier.out_data(a1_mult);
    
    t_adder.in_data_1(t_mult); t_adder.in_data_2(u); t_adder.out_data(t_add_u);
    a0_adder.in_data_1(a0_mult); a0_adder.in_data_2(u); a0_adder.out_data(a0_add_u);
    a1_adder_1.in_data_1(a1_mult); a1_adder_1.in_data_2(hh_1); a1_adder_1.out_data(a1_add_1_to_hh);
    a1_adder_2.in_data_1(a1_mux_out_1); a1_adder_2.in_data_2(const_1); a1_adder_2.out_data(a1_add_1);
    a1_adder_3.in_data_1(a1_mux_out_2); a1_adder_3.in_data_2(a1_t_hh); a1_adder_3.out_data(a1_add_t_hh);
    
    u_multiplexor.in_data_1(u_mult); u_multiplexor.in_data_2(u_mux_t_to_hh); u_multiplexor.control(u_mux_ctrl); u_multiplexor.out_data(u_mux_out);
    t_multiplexor.in_data_1(t_mult); t_multiplexor.in_data_2(t_add_u); t_multiplexor.control(t_mux_ctrl); t_multiplexor.out_data(t_mux_out);
    a0_multiplexor.in_data_1(a0_mult); a0_multiplexor.in_data_2(a0_add_u); a0_multiplexor.control(a0_mux_ctrl); a0_multiplexor.out_data(a0_mux_out);
    a1_multiplexor_1.in_data_1(a1_mult); a1_multiplexor_1.in_data_2(a1_add_1_to_hh); a1_multiplexor_1.control(a1_mux_1_ctrl); a1_multiplexor_1.out_data(a1_mux_out_1);
    a1_multiplexor_2.in_data_1(a1_mux_out_1); a1_multiplexor_2.in_data_2(a1_add_1); a1_multiplexor_2.control(a1_mux_2_ctrl); a1_multiplexor_2.out_data(a1_mux_out_2);
    a1_multiplexor_3.in_data_1(a1_mux_out_2); a1_multiplexor_3.in_data_2(a1_add_t_hh); a1_multiplexor_3.control(a1_mux_3_ctrl); a1_multiplexor_3.out_data(a1_mux_out_3);
    
    t_comparator.in_data_reference(u); t_comparator.in_data_comparison(t); t_comparator.less_than_signal(lt_1);
    a0_comparator.in_data_reference(u); a0_comparator.in_data_comparison(a0); a0_comparator.less_than_signal(lt_2);
    
    t_to_hh.in_data(t); t_to_hh.out_data(u_mux_t_to_hh);

    t_hh_extract.in_data(t); t_hh_extract.out_data(a1_t_hh);
    
    SC_CTHREAD (process_hw_mult, clk.pos());
  }
  
};

#endif /* end _DH_HW_MULT_H_ */
