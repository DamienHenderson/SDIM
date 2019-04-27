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
			return true;
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
		if (next_token.token_type == TokenType::NumericLiteral)
		{
			// process float literals
			Token expect_dot_token = tokens[current_token + 1];
			std::string combined_number = next_token.lexeme;
			if (expect_dot_token.token_type == TokenType::Dot)
			{
				combined_number += expect_dot_token.lexeme;
				Token expect_num_literal_token = tokens[current_token + 2];
				if (expect_num_literal_token.token_type == TokenType::NumericLiteral)
				{
					combined_number += expect_num_literal_token.lexeme;
					// token is float literal
					// look for f or d on the end
					Token expect_f_or_d_token = tokens[current_token + 3];
					if (expect_f_or_d_token.token_type == TokenType::Identifier)
					{
						if (expect_f_or_d_token.lexeme == "f")
						{
							// f32
							F32 num_literal = static_cast<F32>(std::atof(combined_number.c_str()));
							generator->WritePushF32Instruction(program_data, num_literal);
							return ParseExpression(tokens, program_data, generator, current_token + 4);
						}
						else if (expect_f_or_d_token.lexeme == "d")
						{
							// f64
							F64 num_literal = std::atof(combined_number.c_str());
							generator->WritePushF64Instruction(program_data, num_literal);
							return ParseExpression(tokens, program_data, generator, current_token + 4);
						}
						else
						{
							// Coincidental identifier at end
							// TODO: make postscript types on numeric literals a feature of the scanner
							Utils::Log("Unsupported type specifier ", expect_f_or_d_token.lexeme, " at end of floating point literal");
							return ParseExpression(tokens, program_data, generator, current_token + 3);
							
						}
						// missing end also defaults to f64
					}
					else
					{
						// F64
						F64 num_literal = std::atof(combined_number.c_str());
						generator->WritePushF64Instruction(program_data, num_literal);
						return ParseExpression(tokens, program_data, generator, current_token + 3);
					}
				}
				else
				{
					// malformed float literal
					Utils::Log("Malformed float literal ", combined_number);
					return false;
				}
			}
			else
			{
				// Free Integer literals are of type Int32 by default with postscript characters added to the end to force a certain type
				Int32 num_literal = std::atoi(combined_number.c_str());
				generator->WritePushInt32Instruction(program_data, num_literal);
				return ParseExpression(tokens, program_data, generator, current_token + 1);
			}
		}
		if (next_token.token_type == TokenType::Module)
		{
			// module so the following token should be an identifier
			Token expect_module_token = tokens[current_token + 1];
			if (expect_module_token.token_type == TokenType::Identifier)
			{
				// TODO: handle modules correctly
				Utils::Log("Found module: ", expect_module_token.lexeme);
				return ParseExpression(tokens, program_data, generator, current_token + 2);
			}
			else
			{
				// Module names must be an identifier
				Utils::Log(expect_module_token.lexeme, " is not a valid name for a module");
				return ParseExpression(tokens, program_data, generator, current_token + 1);
			}
			
		}
		if (next_token.token_type == TokenType::Identifier)
		{
			// test against built in types
			for (UInt8 i = 0; i < Utils::VariableTypeToUInt8(VariableType::Unknown); i++)
			{
				if (next_token.lexeme == variable_type_strings[i])
				{
					Utils::Log("Found Type specifier for type: ", variable_type_strings[i]);
					// TODO: process type specifier for function and variable declarations
					return ParseExpression(tokens, program_data, generator, current_token + 1);
				}
			}
		}
		return ParseExpression(tokens, program_data, generator, ++current_token);
		// return true;
	}

}