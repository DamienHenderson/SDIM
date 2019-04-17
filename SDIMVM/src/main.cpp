#include <VirtualMachine.hpp>
#include <Utils.hpp>

#include <memory>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: SDIMVM <filename>\n";
		return -1;
	}
	std::unique_ptr<SDIM::VirtualMachine> vm = std::make_unique<SDIM::VirtualMachine>();
	const char* file_name = argv[1];
	bool res = vm->LoadFile(file_name);
	if (!res)
	{
		SDIM::Utils::Log("SDIM Virtual Machine failed to load file: ", file_name, "\n");
		return -1;
	}
	res = vm->RunFile();

	if (!res)
	{
		SDIM::Utils::Log("SDIM Virtual Machine encountered an error whilst running program: ", file_name, "\n");
		return 2;
	}


	
	return 0;
}