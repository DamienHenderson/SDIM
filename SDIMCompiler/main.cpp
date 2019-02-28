#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cassert>

#include "Utils.hpp"
#include "Scanner.hpp"
#include "Token.hpp"


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
	SDIM::Scanner scanner;
	std::vector<SDIM::Token> tokens;
	bool res = scanner.ScanFile(compile_filename, tokens);

	// TODO: Move this into a function
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "--help")
		{
			PrintHelp();
		}
	}

	return 0;
}