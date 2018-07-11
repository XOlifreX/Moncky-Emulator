#include "cl.h"



MonckeyInstruction ControlLogic::getInstructionType(uint16_t instruction) {

	if ((instruction & 0xF000) == MonckeyInstruction::HALT)
		return MonckeyInstruction::HALT;
	if ((instruction & 0xD000) == MonckeyInstruction::LI)
		return MonckeyInstruction::LI;
	// Only check first 2 bits 
	if ((instruction & 0xC000) == MonckeyInstruction::ALU)
		return MonckeyInstruction::ALU;
	if ((instruction & 0xE000) == MonckeyInstruction::LD)
		return MonckeyInstruction::LD;
	if ((instruction & 0xE000) == MonckeyInstruction::ST)
		return MonckeyInstruction::ST;
	if ((instruction & 0xE000) == MonckeyInstruction::JP)
		return MonckeyInstruction::JP;
	if ((instruction & 0xF000) == MonckeyInstruction::PCTO)
		return MonckeyInstruction::PCTO;
	if ((instruction & 0xF000) == MonckeyInstruction::JPC)
		return MonckeyInstruction::JPC;
	return MonckeyInstruction::HALT;

}

MonckyALUInstruction ControlLogic::getAluInstructionType(uint16_t instruction) {

	switch (instruction & 0x0F00) {
	case MonckyALUInstruction::NOP:
		return MonckyALUInstruction::NOP;
	case MonckyALUInstruction::OR:
		return MonckyALUInstruction::OR;
	case MonckyALUInstruction::AND:
		return MonckyALUInstruction::AND;
	case MonckyALUInstruction::XOR:
		return MonckyALUInstruction::XOR;
	case MonckyALUInstruction::ADD:
		return MonckyALUInstruction::ADD;
	case MonckyALUInstruction::SUB:
		return MonckyALUInstruction::SUB;
	case MonckyALUInstruction::SHL:
		return MonckyALUInstruction::SHL;
	case MonckyALUInstruction::SHR:
		return MonckyALUInstruction::SHR;
	case MonckyALUInstruction::ASHR:
		return MonckyALUInstruction::ASHR;
	case MonckyALUInstruction::NOT:
		return MonckyALUInstruction::NOT;
	case MonckyALUInstruction::NEG:
		return MonckyALUInstruction::NEG;
	}
		
	return MonckyALUInstruction::NOP;

}