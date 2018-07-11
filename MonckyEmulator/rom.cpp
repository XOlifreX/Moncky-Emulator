#include "rom.h"


int Rom::get(short pc) {
	return this->code[pc];
}

bool Rom::adressOoB(short pc) {
	return pc >= this->length;
}

void Rom::set(int data[], int length) {
	this->length = length;

	for (int i = 0; i < length; i++)
		this->code[i] = data[i];

}