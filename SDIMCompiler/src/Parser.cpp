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
		
		return ParseExpression(tokens, program_data, generator, 0);
		/*
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
		*/
	}

	bool Parser::ParseExpression(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator, UInt64 current_token)
	{
		if (tokens.empty())
		{
			Utils::Log("No Tokens found in compilation input");
			return false;
		}
		if (current_token >= tokens.size())
		{
			Utils::Log("Reached end of tokens");
			return false;
		}
		Token next_token = tokens[current_token];
		Utils::Log("Parsing token ", next_token.ToString());

		if (Utils::IsOpeningBracket(next_token.token_type))
		{
			brackets_.push(next_token.token_type);
			return ParseExpression(tokens, program_data, generator, ++current_token);
		}
		else if (Utils::IsClosingBracket(next_token.token_type))
		{
			if (brackets_.empty())
			{
				Utils::Log("Closing bracket: ", next_token.lexeme, " found with no matching opening bracket");
				return false;
			}
			TokenType current_bracket = brackets_.top();

			if (!Utils::IsMatchingBracketPair(current_bracket, next_token.token_type))
			{
				Utils::Log("Expected matching bracket for ", Utils::TokenTypeToString(current_bracket), " but got ", Utils::TokenTypeToString(next_token.token_type), "Instead");
				return false;
			}
			Utils::Log("Matched opening bracket ", Utils::TokenTypeToString(current_bracket), " with ", Utils::TokenTypeToString(next_token.token_type));
			brackets_.pop();
		}
		return ParseExpression(tokens, program_data, generator, ++current_token);
		// return true;
	}

}