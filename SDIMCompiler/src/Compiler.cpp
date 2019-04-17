#include "Compiler.hpp"
#include "Scanner.hpp"
#include "Utils.hpp"
namespace SDIM
{
	Compiler::Compiler()
	{
	}


	Compiler::~Compiler()
	{
	}
	bool Compiler::Compile(const std::string& program_string, std::vector<unsigned char>& program_data)
	{
		Scanner scanner;
		std::vector<SDIM::Token> tokens;
		bool res = scanner.ScanString(program_string, tokens);
		if (!res)
		{
			SDIM::Utils::Log("Failed to scan program string\n");
			return false;
		}
		(void)program_data;
		return true;
	}
	bool Compiler::CompileFile(const std::string& file_path, std::vector<unsigned char>& program_data)
	{
		Scanner scanner;
		std::vector<SDIM::Token> tokens;
		bool res = scanner.ScanFile(file_path, tokens);
		if (!res)
		{
			SDIM::Utils::Log("Failed to scan program string\n");
			return false;
		}
		(void)program_data;
		return true;
	}
}