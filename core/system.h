#pragma once
#ifndef SYS_H
#define SYS_H


#include <memory>
#include <iostream>

// #include "IMoncky.h"
#include "cl.h"
#include "registers.h"
#include "ram.h"
#include "rom.h"
#include "alu.h"


// Singleton
class System {
private:
	std::unique_ptr<RegisterPool> registers;
	std::unique_ptr<ControlLogic> cl;
	std::unique_ptr<Alu> alu;
	std::unique_ptr<Ram> ram;
	std::unique_ptr<Rom> rom;
	int pc;

	void exec(MonckeyInstruction type, uint16_t instruction);
	System();
	~System();
public:
	static System& getInstance() {
		static System instance;

		return instance;
	}

	void loadIntoRom(std::string path);
	void loadIntoRom(int data[], int length);
	void runLoop();

};

#endif // !SYS_H