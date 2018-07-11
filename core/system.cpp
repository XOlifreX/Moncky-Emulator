#include "system.h"
#include "cl.h"


System::System() {

	this->registers = std::unique_ptr<RegisterPool>(new RegisterPool());
	this->cl = std::unique_ptr<ControlLogic>(new ControlLogic());
	this->alu = std::unique_ptr<Alu>(new Alu());
	this->ram = std::unique_ptr<Ram>(new Ram());
	this->rom = std::unique_ptr<Rom>(new Rom());
	this->pc = 0;

}

System::~System() {



}


// TODO: Write file reader and initialize it in the rom.
void System::loadIntoRom(std::string path) {

	// (*this->rom).

}

void System::loadIntoRom(int data[], int length) {

	(*this->rom).set(data, length);

}


void System::runLoop() {

	while (!(*this->rom).adressOoB(this->pc)) {

		uint16_t instruction = (*this->rom).get(this->pc);
		MonckeyInstruction type = (*this->cl).getInstructionType(instruction);

		this->exec(type, instruction);
		
	}

}

void System::exec(MonckeyInstruction type, uint16_t instruction) {

	switch (type) {
		// Load an 8 bit variable in a register
	case MonckeyInstruction::LI:
	{
		std::cout << "LI INSTRUCTION" << std::endl;
		int value = (instruction & 0x0FF0) >> 4; // Get the value
		std::cout << "Value = " << value << std::endl;
		short r = instruction & 0x000F;
		std::cout << "Register = " << r << std::endl;

		(*this->registers).loadInRegister(r, value);
		this->pc++;

		std::cout << "LI END: Value inserted in register." << std::endl << std::endl;
	}
	break;
	// Do a operation on the ALU and set the result on a register
	case MonckeyInstruction::ALU:
	{
		std::cout << "ALU INSTRUCTION" << std::endl;
		// exec ALU
		MonckyALUInstruction type = (*this->cl).getAluInstructionType(instruction);

		short r1 = (instruction & 0x00F0) >> 4;
		short r2 = instruction & 0x000F;

		int val1 = (*this->registers).getFromRegister(r1);
		int val2 = (*this->registers).getFromRegister(r2);
		std::cout << "r1 = " << val1 << std::endl;
		std::cout << "r2 = " << val2 << std::endl;

		int value = (*this->alu).doOperation(type, val1, val2);
		std::cout << "After calculation: " << value << std::endl;
		(*this->registers).loadInRegister(r1, value);
		this->pc++;

		std::cout << "ALU END: value inserted in register." << std::endl;
		std::cout << std::endl;
	}
	break;
	// Load a value from ram into a register
	case MonckeyInstruction::LD:
	{
		std::cout << "LD INSTRUCTION" << std::endl;
		// exec LD
		short r1 = (instruction & 0x00F0) >> 4;
		short r2 = instruction & 0x000F;

		int ramIndex = (*this->registers).getFromRegister(r2);
		std::cout << "Address from RAM to load:" << ramIndex << std::endl;

		int val = (*this->ram).get(ramIndex);
		std::cout << "Value from RAM: " << val << std::endl;

		(*this->registers).loadInRegister(r1, val);
		this->pc++;

		std::cout << "LD END: Value inserted in register." << std::endl;
		std::cout << std::endl;
	}
	break;
	// Set a vale from a register in ram.
	case MonckeyInstruction::ST:
	{
		std::cout << "ST INSTRUCTION" << std::endl;
		// exec ST
		short r1 = (instruction & 0x00F0) >> 4;
		short r2 = instruction & 0x000F;

		int val = (*this->registers).getFromRegister(r1);
		std::cout << "Value to insert into RAM: " << val << std::endl;

		int ramIndex = (*this->registers).getFromRegister(r2);
		std::cout << "Address to insert value into RAM: " << ramIndex << std::endl;

		(*this->ram).insert(ramIndex, val);
		this->pc++;

		std::cout << "ST END: Value inserted in RAM." << std::endl;
		std::cout << std::endl;
	}
	break;
	// Set the Program Cont value to a specific value.
	case MonckeyInstruction::JP:
	{
		std::cout << "JP INSTRUCTION" << std::endl;
		// exec JP
		short r1 = instruction & 0x000F;

		std::cout << "Old PC location: " << this->pc << std::endl;
		this->pc = (*this->registers).getFromRegister(r1);
		std::cout << "New PC location: " << this->pc << std::endl;

		std::cout << std::endl;
		std::cout << "JP END: Jumped to new code location." << std::endl;
	}
	break;
	// Set the Program Count value in register
	case MonckeyInstruction::PCTO:
	{
		std::cout << "PCTO INSTRUCTION" << std::endl;
		// exec PCTO
		short r1 = instruction & 0x000F;

		(*this->registers).loadInRegister(r1, this->pc);

		std::cout << "PCTO END: Loaded PC location in the register." << std::endl;
		std::cout << std::endl;
	}
	break;
	// Set the Program Count value to a specific value if a condition is met.
	case MonckeyInstruction::JPC:
	{
		std::cout << "JPC INSTRUCTION" << std::endl;
		// exec JPC
		if ((*this->alu).checkFlagCondition(instruction & 0x0070)) {
			std::cout << "Condition met!" << std::endl;
			short r1 = instruction & 0x000F;

			std::cout << "Old PC location: " << this->pc << std::endl;
			this->pc = (*this->registers).getFromRegister(r1);
			std::cout << "New PC location: " << this->pc << std::endl;
		}
		else
		{
			std::cout << "Condition not met. Will goto next instruction." << std::endl;
			this->pc++;
		}


		std::cout << "JPC END" << std::endl;
		std::cout << std::endl;
	}
	break;
	default:
	{
		// exec HALT
	}
	}
}