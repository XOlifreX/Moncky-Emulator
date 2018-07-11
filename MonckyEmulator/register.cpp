#include "registers.h"


RegisterPool::RegisterPool() {

	

}

RegisterPool::~RegisterPool() {



}

// TODO: throw error if register doesn't exist...
void RegisterPool::loadInRegister(short index, int value) {

	this->r[index] = value;

}

int RegisterPool::getFromRegister(short index) {

	return this->r[index];

}