#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "MonckyCompiler.h"


#ifndef AS_H
#define AS_H

class AssemblerReader {
private:
	MonckyCompiler compiler;
public:
	int* readFile(int* size);
};

#endif // !AS_H
