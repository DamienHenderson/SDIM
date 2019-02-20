#include "VirtualMachine.hpp"

#include <iostream>
int main(int argc, char** argv)
{
	SDIM::VirtualMachine vm;
	bool res = vm.LoadFile("./program.bin");
	
	bool res = vm.RunFile();

	if (!res)
	{
		std::cerr << "SDIM Virtual Machine encountered an error whilst running the program\n";
	}

	char in;
	std::cin >> in;
	
	return 0;
}