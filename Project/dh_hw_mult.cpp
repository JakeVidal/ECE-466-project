#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

#define WAIT_STATE 0
#define EXECUTE_STATE 1
#define OUTPUT_STATE 2
#define FINISH_STATE 3

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

            case EXECUTE_STATE:
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

