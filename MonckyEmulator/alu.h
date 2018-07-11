#include "cl.h"
#include <iostream>

#ifndef ALU_H
#define ALU_H

class Alu {
private:
	short carry;
	short zero;
	short sign;
	short overflow;
	void setFlags(int value);
public:
	int doOperation(MonckyALUInstruction instuction, int val1, int val2);
	bool checkFlagCondition(short condition);
};

#endif // !ALU_H