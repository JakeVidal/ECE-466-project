#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

#define WAIT_STATE 0
#define INPUT_STATE 1
#define LOAD_STATE 2
#define STAGE_STATE 3
#define OUTPUT_STATE 4
#define FINISH_STATE 5

void dh_hw_mult::process_hw_mult()
{
    int counter = 0;

    UINT2 current_state = WAIT_STATE;
    hw_mult_done.write(false);

    while (true)
    {  
        wait();

        switch(current_state)
        {
            case WAIT_STATE:/*
		cout << endl;
		cout << "Multiplication values: WAIT_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u1 = " << u1.read()  << ", u2 = " << u2.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		*/
                if (hw_mult_enable.read() == true)
                {
		  current_state = INPUT_STATE;
                }
                break;

            case INPUT_STATE:/*
		cout << endl;
		cout << "Multiplication values: INPUT_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u1 = " << u1.read()  << ", u2 = " << u2.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: INPUT_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u1 load = " << ld_u1.read() << ", u2 load = " << ld_u2.read() << endl;
		cout << "t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << endl;
		*/
		ld_b.write(1); ld_c.write(1);
		ld_a0.write(0);	ld_a1.write(0);
		a1_mux_1_ctrl.write(0);	a1_mux_2_ctrl.write(0);
		
		current_state = LOAD_STATE;
                break;

            case LOAD_STATE:/*
		cout << endl;
		cout << "Multiplication values: LOAD_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u1 = " << u1.read()  << ", u2 = " << u2.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: LOAD_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u1 load = " << ld_u1.read() << ", u2 load = " << ld_u2.read() << endl;
		cout << "t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << endl;
		*/
		ld_b.write(0); ld_c.write(0);
		ld_a0.write(1);	ld_a1.write(1);
		
		current_state = STAGE_STATE;
		break;

            case STAGE_STATE:/*
		cout << endl;
		cout << "Multiplication values: STAGE2_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u1 = " << u1.read()  << ", u2 = " << u2.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: STAGE2_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u1 load = " << ld_u1.read() << ", u2 load = " << ld_u2.read() << endl;
		cout << "t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << endl;
		*/
		ld_a0.write(0);
		a1_mux_1_ctrl.write(lt_1.read()); a1_mux_2_ctrl.write(lt_2.read());
		
		current_state = OUTPUT_STATE;
                break;


            case OUTPUT_STATE:/*
		cout << endl;
		cout << "Multiplication values: OUTPUT_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u1 = " << u1.read()  << ", u2 = " << u2.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		*/
                out_data_low.write(a0.read());
                out_data_high.write(a1.read());
                hw_mult_done.write(true);

                current_state = FINISH_STATE;
                break;

            case FINISH_STATE:/*
		cout << endl;
		cout << "Multiplication values: FINISH_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u1 = " << u1.read()  << ", u2 = " << u2.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		*/
                if (hw_mult_enable.read() == false)
                {
                    hw_mult_done.write(false);
                    current_state = WAIT_STATE;
                }
/*
                counter++;
                if ((counter % 20) == 0)
                {
		    sc_stop();
                    cout << "Multiplication count: " << counter << endl;
                }*/
                break;
        }
    }  	  
}

