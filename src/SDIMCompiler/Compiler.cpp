#include "Compiler.hpp"
#include "Scanner.hpp"
#include "Utils.hpp"
#include "Parser.hpp"
#include "Generator.hpp"
#include "BytecodeGenerator.hpp"

#include <fstream>
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
		Parser parser;
		BytecodeGenerator gen;
		res = parser.Parse(tokens, program_data, &gen);
		WriteBytecodeHeader(gen.GetHeader(), program_data);
		if (!res)
		{
			SDIM::Utils::Log("Failed to parse program string\n");
			return false;
		}
		return true;
	}
	bool Compiler::CompileFile(const std::string& file_path, std::vector<unsigned char>& program_data)
	{
		(void)file_path;

		BytecodeGenerator gen;
		gen.GetHeader().entrypoint_idx = 1;
		gen.GetHeader().file_comment = "Hello World";

		size_t header_size = sizeof(gen.GetHeader().entrypoint_idx) + gen.GetHeader().file_comment.length() + sizeof(UInt64);
		
		WriteBytecodeHeader(gen.GetHeader(), program_data);
		
		// halt
		size_t halt_idx = program_data.size();
		gen.WriteHaltInstruction(program_data);
		// loop constant
		// declare iterator
		gen.WritePushInt64Instruction(program_data, 0);
		gen.WriteLocalVarInstruction(program_data, 0);
		// test loop
		size_t test_idx = program_data.size() - header_size;
		
		gen.WritePushLocalInstruction(program_data, 0);
		gen.WritePushInt64Instruction(program_data, 10);

		gen.WriteLessInstruction(program_data);
		gen.WriteJumpFalseInstruction(program_data, halt_idx - header_size);

		gen.WritePushLocalInstruction(program_data, 0);
		gen.WritePushInt64Instruction(program_data, 1);
		gen.WriteAddInstruction(program_data);
		gen.WriteLocalVarInstruction(program_data, 0);


		gen.WritePushStringInstruction(program_data, "Hello world");
		gen.WriteVMCallInstruction(program_data, 1);
		gen.WriteJumpInstruction(program_data, test_idx - header_size);



		return true;
		/*
		Scanner scanner;
		std::vector<SDIM::Token> tokens;
		bool res = scanner.ScanFile(file_path, tokens);
		if (!res)
		{
			SDIM::Utils::Log("Failed to scan program file\n");
			return false;
		}
		Parser parser;
		BytecodeGenerator gen;
		res = parser.Parse(tokens, program_data, &gen);
		WriteBytecodeHeader(gen.GetHeader(), program_data);
		if (!res)
		{
			SDIM::Utils::Log("Failed to parse program file\n");
			return false;
		}
		
		return true;
		*/
	}
}