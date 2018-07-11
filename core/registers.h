#pragma once

#ifndef RG_H
#define RG_H

enum Register {
	R1 = 0x0,
	R2 = 0x1,
	R3 = 0x2,
	R4 = 0x3,
	R5 = 0x4,
	R6 = 0x5,
	R7 = 0x6,
	R8 = 0x7,
	R9 = 0x8,
	R10 = 0x9,
	R11 = 0xA,
	R12 = 0xB,
	R13 = 0xC,
	R14 = 0xD,
	R15 = 0xE,
	R16 = 0xF
};

class RegisterPool {
private:
	int r[16];
public:
	RegisterPool();
	~RegisterPool();
	void loadInRegister(short index, int value);
	int getFromRegister(short index);

};

#endif // !RG_H
