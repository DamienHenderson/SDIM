#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cassert>

// #include "Utils.hpp"
#include "Scanner.hpp"
#include "Token.hpp"
#include "Compiler.hpp"
#include <Utils.hpp>

void PrintHelp()
{
	std::cout << "SDIM Compiler\n";
	std::cout << "Type ./sdimcompiler <filename> to compile the given file\n";
}
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Expected compilation filename and options but got no command line args\n";
		return 1;
	}
	std::string compile_filename = argv[1];
	std::cout << "Attempting to compile: " << compile_filename << "\n";
	SDIM::Compiler compiler;
	std::vector<unsigned char> prog_data;
	bool res = compiler.CompileFile(compile_filename, prog_data);
	if (!res)
	{
		std::cerr << "Failed to compile file: " << compile_filename << "\n";
		return -1;
	}
	std::fstream test_file_refactor_this("test.bin", std::ios::out | std::ios::binary);
	if (!test_file_refactor_this.good())
	{
		SDIM::Utils::Log("Failed to open test binary file\n");
		return -1;
	}
	
	test_file_refactor_this.write((const char*)prog_data.data(), prog_data.size());
	test_file_refactor_this.close();
	// TODO: Move this into a function
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "--help")
		{
			PrintHelp();
		}
	}
	std::cout << "FNV1A hash of test is: " << SDIM::Utils::FNV1AHash("test", std::strlen("test")) << "\n";
	return 0;
}