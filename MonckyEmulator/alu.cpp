#include "alu.h"


int Alu::doOperation(MonckyALUInstruction instuction, int val1, int val2) {

	int result = 0;

	switch (instuction) {
	case MonckyALUInstruction::OR:
		std::cout << "ALU instruction: OR" << std::endl;
		result =  val1 | val2;
		break;
	case MonckyALUInstruction::AND:
		std::cout << "ALU instruction: AND" << std::endl;
		result =  val1 & val2;
		break;
	case MonckyALUInstruction::XOR:
		std::cout << "ALU instruction: XOR" << std::endl;
		result =  val1 ^ val2;
		break;
	case MonckyALUInstruction::ADD:
		std::cout << "ALU instruction: ADD" << std::endl;
		result =  val1 + val2;
		break;
	case MonckyALUInstruction::SUB:
		std::cout << "ALU instruction: SUB" << std::endl;
		result =  val1 - val2;
		break;
	case MonckyALUInstruction::SHL:
		std::cout << "ALU instruction: SHL" << std::endl;
		result =  val1 << val2;
		break;
	case MonckyALUInstruction::SHR:
		std::cout << "ALU instruction: SHR" << std::endl;
		result =  val1 >> val2;
		break;
	case MonckyALUInstruction::ASHR:
		std::cout << "ALU instruction: ASHR" << std::endl;
		result =  0; // todo
		break;
	case MonckyALUInstruction::NOT:
		std::cout << "ALU instruction: NOT" << std::endl;
		result =  ~val1;
		break;
	case MonckyALUInstruction::NEG:
		std::cout << "ALU instruction: NEG" << std::endl;
		result =  val1 * val2; // val2 should be -1
		break;
	default:
		// NOP instruction
		std::cout << "ALU instruction: NOP" << std::endl;
		result =  0;
	}

	this->setFlags(result);

	return result;

}


void Alu::setFlags(int value) {

	// Check for overflow & carry (and underflow)
	if (value > 32767) {
		value = (value - 32767) + -32767;
		this->overflow = MonckeyConditionIntruction::O;
		this->carry = MonckeyConditionIntruction::C;
	}
	else if (value < -32767) {
		value = ((value + 32767) * -1) - 32767;
		this->overflow = MonckeyConditionIntruction::O;
		this->carry = MonckeyConditionIntruction::C;
	}
	else {
		this->overflow = MonckeyConditionIntruction::NO;
		this->carry = MonckeyConditionIntruction::NC;
	}


	// Check for zero
	this->zero = value == 0 ? MonckeyConditionIntruction::Z : MonckeyConditionIntruction::NZ;

	// Check for sign
	this->sign = value >= 0 ? MonckeyConditionIntruction::NS : MonckeyConditionIntruction::S;

}

bool Alu::checkFlagCondition(short condition) {

	switch (condition) {
	case MonckeyConditionIntruction::C:
		std::cout << "Condition instruction: C" << std::endl;
		std::cout << "Carry: " << this->carry << std::endl;
		return this->carry == MonckeyConditionIntruction::C;
	case MonckeyConditionIntruction::NC:
		std::cout << "Condition instruction: NC" << std::endl;
		std::cout << "Carry: " << this->carry << std::endl;
		return this->carry == MonckeyConditionIntruction::NC;
	case MonckeyConditionIntruction::Z:
		std::cout << "Condition instruction: Z" << std::endl;
		std::cout << "Zero: " << this->zero << std::endl;
		return this->zero == MonckeyConditionIntruction::Z;
	case MonckeyConditionIntruction::NZ:
		std::cout << "Condition instruction: NZ" << std::endl;
		std::cout << "Zero: " << this->zero << std::endl;
		return this->zero == MonckeyConditionIntruction::NZ;
	case MonckeyConditionIntruction::S:
		std::cout << "Condition instruction: S" << std::endl;
		std::cout << "Sign: " << this->sign << std::endl;
		return this->sign == MonckeyConditionIntruction::S;
	case MonckeyConditionIntruction::NS:
		std::cout << "Condition instruction: NS" << std::endl;
		std::cout << "Sign: " << this->sign << std::endl;
		return this->sign == MonckeyConditionIntruction::NS;
	case MonckeyConditionIntruction::O:
		std::cout << "Condition instruction: O" << std::endl;
		std::cout << "Overflow: " << this->overflow << std::endl;
		return this->overflow == MonckeyConditionIntruction::O;
	case MonckeyConditionIntruction::NO:
		std::cout << "Condition instruction: NO" << std::endl;
		std::cout << "Overflow: " << this->overflow << std::endl;
		return this->overflow == MonckeyConditionIntruction::NO;
	}

}