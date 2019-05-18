#pragma once

#include <string>
#include <vector>

namespace SDIM
{
	// Takes tokens from the scanner and converts it to a bytecode file
	class Compiler
	{
	public:
		Compiler();
		~Compiler();
		// compiles a program directly from a string
		bool Compile(const std::string& program_string, std::vector<unsigned char>& program_data);
		// compiles a program read from the given file
		// program data will be written with the bytecode output of the compiler ready to be written to a file or run by the vm
		bool CompileFile(const std::string& file_path, std::vector<unsigned char>& program_data);
	private:
		// has the compiler encountered an error
		// bool error_state_{ false };


	};
}
