#include "ram.h"


void Ram::insert(short address, int value) {

	this->memory[address] = value;

}

int Ram::get(short address) {

	return this->memory[address];

}