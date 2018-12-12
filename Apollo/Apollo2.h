#ifndef Apollo2_h
#define Apollo2_h

#include "Arduino.h"

class Apollo2{
	public:
	
		Apollo2();
	
		void setLED(bool state);
		void enableDebug(bool state);
		int sensor[9] = {0,27,26,33,32,35,34,39,36};
		int motor[11] = {0,13,15,2,4,16,12,14,21,22,25};
		int A = 0, B = 1, Y = 2, X = 3, UP = 4, DN = 5, LT = 6, RT = 7, 
		    L1 = 8, L2 = 9, L3 = 10, R1 = 11, R2 = 12, R3 = 13,
			LX = 14, LY = 15, RX = 16, RY = 17, Start = 18, Select = 19;
		int _LED = 32; //32
		
	
	private:
		
		
		bool debugState = false;
		
};

		
#endif