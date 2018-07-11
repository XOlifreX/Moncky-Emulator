#include <array>

#ifndef CL_H
#define CL_H

// First 4 bits
enum MonckeyInstruction {
	HALT = 0x0000, // 0000
	LI   = 0x1000, // 00x1
	ALU  = 0x4000, // 01xx
	LD   = 0x8000, // 100x
	ST   = 0xA000, // 101x
	JP   = 0xC000, // 110x
	PCTO = 0xE000, // 1110
	JPC  = 0xF000  // 1111
};

// Extra 4 bits identifying ALU instruction
enum MonckyALUInstruction {
	NOP = 0x0000, // 0000
	OR = 0x0100, // 0001
	AND = 0x0200, // 0010
	XOR = 0x0300, // 0011
	ADD = 0x0400, // 0100
	SUB = 0x0500, // 0101
	SHL = 0x0600, // 0110
	SHR = 0x0700, // 0111
	ASHR = 0x0800, // 1000
	NOT = 0x0900, // 1001
	NEG = 0x0A00  // 1010
};

// Last 3 bits identifying carry information
enum MonckeyConditionIntruction {
	C  = 0x0000, // 0000
	NC = 0x0010, // 0001
	Z  = 0x0020, // 0010
	NZ = 0x0030, // 0011
	S  = 0x0040, // 0100
	NS = 0x0050, // 0101
	O  = 0x0060, // 0110
	NO = 0x0070  // 0111
};


class ControlLogic {
private:
public:
	MonckeyInstruction getInstructionType(uint16_t instruction);
	MonckyALUInstruction getAluInstructionType(uint16_t instruction);
};

#endif // !CL_H