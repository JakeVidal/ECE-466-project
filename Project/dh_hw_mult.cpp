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
    UINT2 current_state = WAIT_STATE;
    hw_mult_done.write(false);

    while (true)
    {  
        switch(current_state)
        {
            case WAIT_STATE:
                if (hw_mult_enable.read() == true)
                {
                	ld_b.write(1); ld_c.write(1);
					ld_a0.write(0);	ld_a1.write(0);
					a1_mux_1_ctrl.write(0);	a1_mux_2_ctrl.write(0);

		  			current_state = LOAD_STATE;
                }
                break;

            case LOAD_STATE:
				ld_b.write(0); ld_c.write(0);
				ld_a0.write(1);	ld_a1.write(1);
				a1_mux_1_ctrl.write(lt_1.read()); a1_mux_2_ctrl.write(lt_2.read());
		
				current_state = DEASSERT_STATE;
                break;

            case DEASSERT_STATE:
				ld_a0.write(0); ld_a1.write(0);
				
				current_state = OUTPUT_STATE;
                break;

            case OUTPUT_STATE:
                out_data_low.write(a0.read());
                out_data_high.write(a1.read());
                hw_mult_done.write(true);

                current_state = FINISH_STATE;
                break;

            case FINISH_STATE:
                if (hw_mult_enable.read() == false)
                {
                    hw_mult_done.write(false);
                    current_state = WAIT_STATE;
                }
                break;
        }
		wait();
    }  	  
}

