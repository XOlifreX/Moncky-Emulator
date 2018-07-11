#pragma once

#ifndef ROM_H
#define ROM_H

/// 4MB ROM
class Rom {
private:
	int code[256];
	int length;
public:
	int get(short pc);
	bool adressOoB(short pc);
	void set(int data[], int length);
};

#endif // !ROM_H