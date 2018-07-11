#include <iostream>
#include "cl.h"
#include "system.h"
#include "assemblerReader.h"


int main() {

	/*int code[] = { 
		0x12A0, 
		0x1031, 
		0xA010,
		0x12A0,
		0x8010,
		0x1032, //0x1042,
		0x1103,
		0x4512,
		0xF033,
		0x12A0,
		0x8010,
		0x1012,
		0x4412,
		0xA010,
		0x1150,
		0xC000,
		0x12A0,
		0x8010,
		0x1012,
		0x4512,
		0xA010,
		0x0000
	};*/

	AssemblerReader reader;

	int size = 0;
	int* temp = reader.readFile(&size);

	int code[100];
	for (short i = 0; i < size; i++) {
		code[i] = *(temp + i);
	}

	System& system{ System::getInstance() };
	
	system.loadIntoRom(code, size);
	system.runLoop();

	std::cin.get();

}