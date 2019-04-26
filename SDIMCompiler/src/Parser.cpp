#include "Parser.hpp"

#include <Utils.hpp>

#include "BytecodeGenerator.hpp"
#include "OperatorPrecedence.hpp"
namespace SDIM
{

	Parser::Parser()
	{
	}


	Parser::~Parser()
	{
	}

	bool Parser::Parse(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)program_data;
		
		// Utilises pratt parsing 
		// inspired by this webpage http://journal.stuffwithstuff.com/2011/03/19/pratt-parsers-expression-parsing-made-easy/
		// also inspired by this webpage http://craftinginterpreters.com/compiling-expressions.html
		// also inspired by other sources 
		
		
		generator->WritePushUInt8Instruction(program_data, 42);
		generator->WritePushUInt16Instruction(program_data, 42);
		generator->WritePushUInt32Instruction(program_data, 42);
		generator->WritePushUInt64Instruction(program_data, 42);

		generator->WritePushInt8Instruction(program_data, 42);
		generator->WritePushInt16Instruction(program_data, 42);
		generator->WritePushInt32Instruction(program_data, 42);
		generator->WritePushInt64Instruction(program_data, 42);

		generator->WritePushF32Instruction(program_data, 42.42f);
		generator->WritePushF64Instruction(program_data, 42.42);
		generator->WritePushF64Instruction(program_data, 42.42);
		generator->WritePushF64Instruction(program_data, 42.42);
		generator->WriteAddInstruction(program_data);
		generator->WriteLessInstruction(program_data);

		generator->WriteHaltInstruction(program_data);

		for (size_t idx = 0; idx < tokens.size(); ++idx)
		{
			Token current_token = tokens[idx];

			SDIM::Utils::Log("Token[", idx, "]: ", current_token.ToString(), "\n");
		}
		return !error_state_;
	}

}