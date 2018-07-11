#pragma once


#ifndef RAM_H
#define RAM_H

class Ram {
private:
	int memory[256];
public:
	~Ram() {
		delete memory;
	}

	void insert(short address, int value);
	int get(short address);
};

#endif // !RAM_H