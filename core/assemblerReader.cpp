#include "assemblerReader.h"



int* AssemblerReader::readFile(int* size) {

	std::string line;
	std::ifstream myfile("test1.txt");

	std::vector<int>* instructions = new std::vector<int>();
	int counter = 1;
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			if(line.length() > 0)
				(*instructions).push_back(
					this->compiler.translateAssemblerInstruction(line, counter)
				);
			counter++;
		}
		myfile.close();
	}

	*(size) = (*instructions).size();
	return &(*instructions)[0];

}