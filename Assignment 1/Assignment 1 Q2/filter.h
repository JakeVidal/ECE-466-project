#include "systemc.h"
#include "modules.h"

SC_MODULE(filter){
	sc_in_clk CLK;
	sc_in <bool> RST;
	sc_in <float> XIN;
	sc_out <float> YOUT;

	adder A1, A2, A3, A4;
	multiplier M1, M2, M3;
	clkregister R1, R2;

	sc_signal <float> M1_A1, A1_R1, R1_M2R2, M2_A2, A2_M1A4, M3_A2, A3_M3, R2_A3A4;

	sc_signal <float> mval1, mval2, mval3;


	SC_CTOR(filter):
	A1("A1"), A2("A2"), A3("A3"), A4("A4"), 
	M1("M1"), M2("M2"), M3("M3"), 
	R1("R1"), R2("R2")
	{

	        mval1.write(-1);
	        mval2.write(0.5);
	        mval3.write(0.25);

		A1.NUM1(XIN);
		A1.NUM2(M1_A1);
		A1.OUT(A1_R1);

		A2.NUM1(M2_A2);
		A2.NUM2(M3_A2);
		A2.OUT(A2_M1A4);

		A3.NUM1(XIN);
		A3.NUM2(R2_A3A4);
		A3.OUT(A3_M3);

		A4.NUM1(R2_A3A4);
		A4.NUM2(A2_M1A4);
		A4.OUT(YOUT);

		M1.NUM1(mval1);
		M1.NUM2(A2_M1A4);
		M1.OUT(M1_A1);

		M2.NUM1(mval2);
		M2.NUM2(R1_M2R2);
		M2.OUT(M2_A2);

		M3.NUM1(mval3);
		M3.NUM2(A3_M3);
		M3.OUT(M3_A2);

		R1.CLK(CLK);
		R1.RST(RST);
		R1.IN(A1_R1);
		R1.OUT(R1_M2R2);

		R2.CLK(CLK);
		R2.RST(RST);
		R2.IN(R1_M2R2);
		R2.OUT(R2_A3A4);
	}
};
