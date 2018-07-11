#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdlib.h>

#include "cl.h"


#ifndef MC_H
#define MC_H

class MonckyCompiler {
private:
	int compileLI(const std::vector<std::string> instruction_info);
	int compileLD(const std::vector<std::string> instruction_info);
	int compileST(const std::vector<std::string> instruction_info);
	int compileJP(const std::vector<std::string> instruction_info);
	int compilePCTO(const std::vector<std::string> instruction_info);
	int compileJPCondition(const std::vector<std::string> instruction_info);
	int compileALU(const std::vector<std::string> instruction_info);

	short getAluInstructionType(const std::string alu);
	short getConditionalType(const std::string condition);
	std::vector<std::string> split(const std::string &s, char d);
public:
	MonckyCompiler();
	~MonckyCompiler();
	int translateAssemblerInstruction(std::string instruction, int index);
	int translateBinaryInstruction(std::string instruction);
};

#endif // !MC_H
