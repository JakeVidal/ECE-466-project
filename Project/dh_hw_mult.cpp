#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

#define WAIT_STATE 0
#define INPUT_STATE 1
#define LOAD_STATE 2
#define STAGE1_STATE 3
#define STAGE2_STATE 4
#define STAGE3_STATE 5
#define STAGE4_STATE 6
#define OUTPUT_STATE 7
#define FINISH_STATE 8

void dh_hw_mult::process_hw_mult()
{
	
    NN_DIGIT a[2];
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
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
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
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: INPUT_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u load = " << ld_u.read() << endl;
		cout << "u mux = " << u_mux_ctrl.read() << ", t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << ", a[1] mux 3 = " << a1_mux_3_ctrl.read() << endl;
		*/
		ld_b.write(1); ld_c.write(1);
		ld_u.write(0); ld_t.write(0);
		ld_a0.write(0);	ld_a1.write(0);
		u_mux_ctrl.write(0); t_mux_ctrl.write(0); a0_mux_ctrl.write(0);
		a1_mux_1_ctrl.write(0);	a1_mux_2_ctrl.write(0);
		
		current_state = LOAD_STATE;
                break;

            case LOAD_STATE:/*
		cout << endl;
		cout << "Multiplication values: LOAD_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: LOAD_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u load = " << ld_u.read() << endl;
		cout << "u mux = " << u_mux_ctrl.read() << ", t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << ", a[1] mux 3 = " << a1_mux_3_ctrl.read() << endl;
		*/
		ld_b.write(0); ld_c.write(0);
		ld_u.write(1); ld_t.write(1);
		ld_a0.write(1);	ld_a1.write(1);
		
		current_state = STAGE1_STATE;
		break;

            case STAGE1_STATE:/*
		cout << endl;
		cout << "Multiplication values: STAGE1_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: STAGE1_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u load = " << ld_u.read() << endl;
		cout << "u mux = " << u_mux_ctrl.read() << ", t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << ", a[1] mux 3 = " << a1_mux_3_ctrl.read() << endl;
		*/
		ld_u.write(0); ld_a0.write(0); ld_a1.write(0);
		t_mux_ctrl.write(1);
		
		current_state = STAGE2_STATE;
		break;

            case STAGE2_STATE:/*
		cout << endl;
		cout << "Multiplication values: STAGE2_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: STAGE2_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u load = " << ld_u.read() << endl;
		cout << "u mux = " << u_mux_ctrl.read() << ", t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << ", a[1] mux 3 = " << a1_mux_3_ctrl.read() << endl;
		*/
		ld_u.write(1); ld_t.write(0); ld_a1.write(1);
		u_mux_ctrl.write(1); a1_mux_1_ctrl.write(lt_1.read());
		
		current_state = STAGE3_STATE;
                break;

            case STAGE3_STATE:/*
		cout << endl;
		cout << "Multiplication values: STAGE3_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: STAGE3_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u load = " << ld_u.read() << endl;
		cout << "u mux = " << u_mux_ctrl.read() << ", t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << ", a[1] mux 3 = " << a1_mux_3_ctrl.read() << endl;
		*/
	      	ld_u.write(0); ld_a0.write(1); ld_a1.write(0);
		a0_mux_ctrl.write(1);
		
		current_state = STAGE4_STATE;
                break;

            case STAGE4_STATE:/*
		cout << endl;
		cout << "Multiplication values: STAGE4_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		cout << endl;
		cout << "Control values: STAGE4_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] load = " << ld_a0.read() << ", a[1] load = " << ld_a1.read() << ", b load = " << ld_b.read() << ", c load = " << ld_c.read() << ", t load = " << ld_t.read() << ", u load = " << ld_u.read() << endl;
		cout << "u mux = " << u_mux_ctrl.read() << ", t mux = " << t_mux_ctrl.read() << ", a[0] mux = " << a0_mux_ctrl.read() << ", a[1] mux 1 = " << a1_mux_1_ctrl.read() << ", a[1] mux 2 = " << a1_mux_2_ctrl.read() << ", a[1] mux 3 = " << a1_mux_3_ctrl.read() << endl;
		*/
		ld_u.write(0); ld_a0.write(0); ld_a1.write(1);
		a1_mux_2_ctrl.write(lt_2.read());
		
		current_state = OUTPUT_STATE;
                break;

            case OUTPUT_STATE:/*
		cout << endl;
		cout << "Multiplication values: OUTPUT_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		*/
		a[0] = a0.read();
		a[1] = a1.read();
                out_data_low.write(a[0]);
                out_data_high.write(a[1]);
                hw_mult_done.write(true);

                current_state = FINISH_STATE;
                break;

            case FINISH_STATE:/*
		cout << endl;
		cout << "Multiplication values: FINISH_STATE" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "a[0] = " << a0.read() << ", a[1] = " << a1.read() << ", b = " << b.read() << ", c = " << c.read() << ", t = " << t.read() << ", u = " << u.read() << endl;
		cout << "bHigh = " << b_hh.read() << ", bLow = " << b_lh.read() << ", cHigh = " << c_hh.read() << ", cLow = " << c_lh.read() << endl;
		*/
                if (hw_mult_enable.read() == false)
                {
                    hw_mult_done.write(false);
                    current_state = WAIT_STATE;
                }

                counter++;
                if ((counter % 100) == 0)
                {
                    cout << "Multiplication count: " << counter << endl;
                }
                break;
        }
    }  	  
}

