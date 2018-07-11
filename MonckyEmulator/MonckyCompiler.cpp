#include "MonckyCompiler.h"


short getNumberOfRegister(std::string r) {
	//char* number = (char*) std::malloc(sizeof(char) * r.size());
	if (r.find(",") == std::string::npos) {
		r = r.substr(0, r.size() - 2);
	}
	std::string number = r.substr(1, r.size());

	return std::stoi(number);
}

std::vector<std::string> MonckyCompiler::split(const std::string &s, char d) {
	std::vector<std::string> elems;
	std::istringstream iss(s);

	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter(elems));

	return elems;
}


int MonckyCompiler::translateAssemblerInstruction(std::string instruction, int index) {

	if (instruction.length() > 0) {

		std::vector<std::string> instruction_info = this->split(instruction, ' ');

		if (instruction_info.at(0) == "li")
			return this->compileLI(instruction_info);
		if (instruction_info.at(0) == "ld")
			return this->compileLD(instruction_info);
		if (instruction_info.at(0) == "st")
			return this->compileST(instruction_info);
		if (instruction_info.at(0) == "jp")
			return this->compileJP(instruction_info);
		if (instruction_info.at(0) == "pcto")
			return this->compilePCTO(instruction_info);

		int value = this->compileJPCondition(instruction_info);
		if (value <= 0)
			return value;

		value = this->compileALU(instruction_info);
		if (value <= 0)
			return value;
	}

	return 0x0000;

}

int MonckyCompiler::compileLI(const std::vector<std::string> instruction_info) {

	// Instruction forming
	int li = 0x1000;

	// Get the value (register?)
	// But, is the syntax correct?
	if (instruction_info.at(2)[0] != 'r') {
		short r = std::stoi(instruction_info.at(2));

		li = (li & 0xF00F) | ((r << 4) & 0x0FF0);
	}
	else
	{
		// TODO: compile errors
	}

	// Get destination register
	// But, is the syntax correct? Let's check if the register starts with 'r'.
	if (instruction_info.at(1)[0] == 'r') {
		short r = getNumberOfRegister(instruction_info.at(1));

		li = (li & 0xFFF0) | (r & 0x000F);
	}
	else
	{
		// TODO: compile errors
	}

	return li;

}

int MonckyCompiler::compileLD(std::vector<std::string> instruction_info) {

	// Instruction forming
	int ld = 0x8000;

	// Get destination register
	// But, is the syntax correct? Let's check if the register starts with 'r'.
	if (instruction_info.at(1)[0] == 'r') {
		short r = getNumberOfRegister(instruction_info.at(1));

		ld = (ld & 0xFF0F) | ((r << 4) & 0x00F0);
	}
	else
	{
		// TODO: compile errors
	}

	// Get the register number which contains the ram address of the wanted value
	// But, is the syntax correct?
	if (instruction_info.at(2)[0] == '(' && instruction_info.at(2)[1] == 'r'
		&& instruction_info.at(2)[instruction_info.size() - 1] == ')') {
		short r = std::stoi(instruction_info.at(2).substr(1, instruction_info.at(2).size() - 3));

		ld = (ld & 0xFFF0) | (r & 0x000F);
	}
	else
	{
		// TODO: compile errors
	}

	return ld;

}

int MonckyCompiler::compileST(std::vector<std::string> instruction_info) {

	// Instruction forming
	int st = 0xA000;

	// Get destination register
	// But, is the syntax correct? Let's check if the register starts with 'r'.
	if (instruction_info.at(1)[0] == 'r') {
		short r = getNumberOfRegister(instruction_info.at(1));

		st = (st & 0xFF0F) | ((r << 4) & 0x00F0);
	}
	else
	{
		// TODO: compile errors
	}

	// Get the register number which contains the ram address of the wanted value
	// But, is the syntax correct?
	if (instruction_info.at(2)[0] == '(' && instruction_info.at(2)[1] == 'r'
		&& instruction_info.at(2)[instruction_info.size() - 1] == ')') {
		short r = std::stoi(instruction_info.at(2).substr(1, instruction_info.at(2).size() - 3));

		st = (st & 0xFFF0) | (r & 0x000F);
	}
	else
	{
		// TODO: compile errors
	}

	return st;

}

int MonckyCompiler::compileJP(std::vector<std::string> instruction_info) {

	// Instruction forming
	int jp = 0xC000;

	// Get destination register
	// But, is the syntax correct? Let's check if the register starts with 'r'.
	if (instruction_info.at(1)[0] == 'r') {
		short r = getNumberOfRegister(instruction_info.at(1));

		jp = (jp & 0xFFF0) | (r & 0x000F);
	}
	else
	{
		// TODO: compile errors
	}

	return jp;

}

int MonckyCompiler::compilePCTO(std::vector<std::string> instruction_info) {

	// Instruction forming
	int pcto = 0xE000;

	// Get destination register
	// But, is the syntax correct? Let's check if the register starts with 'r'.
	if (instruction_info.at(1)[0] == 'r') {
		short r = getNumberOfRegister(instruction_info.at(1));

		pcto = (pcto & 0xFFF0) | (r & 0x000F);
	}
	else
	{
		// TODO: compile errors
	}

	return pcto;

}

int MonckyCompiler::compileJPCondition(std::vector<std::string> instruction_info) {

	if (instruction_info.at(0).find("jp") && instruction_info.at(0).size() > 2) {
		// Instruction forming
		int jpc = 0xF000;

		// Get destination register
		// But, is the syntax correct? Let's check if the register starts with 'r'.
		if (instruction_info.at(2)[0] == 'r') {
			short r = getNumberOfRegister(instruction_info.at(1));

			jpc = (jpc & 0xFFF0) | (r & 0x000F);
		}
		else
		{
			// TODO: compile errors
		}

		short c = this->getConditionalType(instruction_info.at(1));

		jpc = (jpc & 0xFF8F) | ((c << 4) & 0x0070);

		return jpc;
	}

	return -1;

}

int MonckyCompiler::compileALU(const std::vector<std::string> instruction_info) {

	// This check needs to be done, cause the compileALU method is the last check if all the other instruction name checks have failed.
	// We either could check if the instruction name is one of the ALU instruction names, but that would require an extra forloop with string comparisons.
	// Instead, since it's the last instruction name check anyway, we can safely check if we're dealing with a HALT instruction.
	if (instruction_info.at(0) != "halt") {
		// Instruction forming
		int alu = 0x4000;

		int instr = this->getAluInstructionType(instruction_info.at(1));
		alu = (alu & 0xF0FF) | ((instr << 8) & 0x0F00);

		// Get destination register
		// But, is the syntax correct? Let's check if the register starts with 'r'.
		if (instruction_info.at(2)[0] == 'r') {
			short r = getNumberOfRegister(instruction_info.at(2));

			alu = (alu & 0xFF0F) | ((r << 4) & 0x00F0);
		}
		else
		{
			// TODO: compile errors
		}

		// Get destination register
		// But, is the syntax correct? Let's check if the register starts with 'r'.
		if (instruction_info.at(3)[0] == 'r') {
			short r = getNumberOfRegister(instruction_info.at(3));

			alu = (alu & 0xFFF0) | (r & 0x000F);
		}
		else
		{
			// TODO: compile errors
		}

		return alu;

	}

	return -1;

}


short MonckyCompiler::getConditionalType(const std::string condition) {

	if (condition.size() == 3) {
		switch (condition[2]) {
		case 'c':
			return 0x0;
		case 'z':
			return 0x2;
		case 's':
			return 0x4;
		default:
			return 0x6;
		}
	}
	else {
		switch (condition[2]) {
		case 'c':
			return 0x1;
		case 'z':
			return 0x3;
		case 's':
			return 0x5;
		default:
			return 0x7;
		}
	}

}


short MonckyCompiler::getAluInstructionType(const std::string alu) {

	if (alu == "OR")
		return 0x1;
	if (alu == "AND")
		return 0x2;
	if (alu == "XOR")
		return 0x3;
	if (alu == "ADD")
		return 0x4;
	if (alu == "SUB")
		return 0x5;
	if (alu == "SHL")
		return 0x6;
	if (alu == "SHR")
		return 0x7;
	if (alu == "ASHR")
		return 0x8;
	if (alu == "NOT")
		return 0x9;
	if (alu == "NEG")
		return 0xA;

	return 0x0;

}