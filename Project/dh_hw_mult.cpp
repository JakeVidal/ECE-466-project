#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

#define WAIT_STATE 0
//#define EXECUTE_STATE 1

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
	
    NN_DIGIT a[2], b, c, t, u;
    NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

    UINT2 current_state = WAIT_STATE;
    hw_mult_done.write(false);

    for (;;)
    {  
        switch(current_state)
        {
            case WAIT_STATE:
                if (hw_mult_enable.read() == true)
                {
                  current_state = EXECUTE_STATE;
                }
                break;

            /*case EXECUTE_STATE:
                b = in_data_1.read();
                c = in_data_2.read();

                bHigh = (NN_HALF_DIGIT)HIGH_HALF (b);
                bLow = (NN_HALF_DIGIT)LOW_HALF (b);
                cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
                cLow = (NN_HALF_DIGIT)LOW_HALF (c);

                a[0] = (NN_DIGIT)bLow * (NN_DIGIT)cLow;
                t = (NN_DIGIT)bLow * (NN_DIGIT)cHigh;
                u = (NN_DIGIT)bHigh * (NN_DIGIT)cLow;
                a[1] = (NN_DIGIT)bHigh * (NN_DIGIT)cHigh;

                if ((t += u) < u) a[1] += TO_HIGH_HALF (1);
                u = TO_HIGH_HALF (t);

                if ((a[0] += u) < u) a[1]++;
                a[1] += HIGH_HALF (t);

                current_state = OUTPUT_STATE;
                break;*/

            case INPUT_STATE:
                break;

            case LOAD_STATE:
                break;

            case STAGE1_STATE:
                break;

            case STAGE2_STATE:
                break;

            case STAGE3_STATE:
                break;

            case STAGE4_STATE:
                break;

            case OUTPUT_STATE:
                out_data_low.write(a[0]);
                out_data_high.write(a[1]);
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

