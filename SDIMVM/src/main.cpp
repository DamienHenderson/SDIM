#include <VirtualMachine.hpp>
#include <iostream>
int main(int argc, char** argv)
{
	SDIM::VirtualMachine vm;
	bool res = vm.LoadFile("./program.bin");
	if (!res)
	{
		std::cerr << "SDIM Virtual Machine failed to load file\n";
		return 1;
	}
	res = vm.RunFile();

	if (!res)
	{
		std::cerr << "SDIM Virtual Machine encountered an error whilst running the program\n";
		return 2;
	}

	char in;
	std::cin >> in;
	
	return 0;
}