#pragma once

#include "MonckyCompiler.h"
#include <vector>


#ifndef FR_H
#define FR_H

class FileReader {
private:
	MonckyCompiler compiler;
public:
	FileReader();
	~FileReader();
	MonckyCompiler getCompiler();
	virtual int* readFile(int* size) = 0;
	
};

#endif // !FR_H
