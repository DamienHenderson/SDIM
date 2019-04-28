#include "Parser.hpp"

#include <Utils.hpp>

#include <random>

#include "BytecodeGenerator.hpp"
#include "OperatorPrecedence.hpp"
namespace SDIM
{

	Parser::Parser()
	{
		rng_ = std::make_unique<std::default_random_engine>((std::random_device())());
		
		
	}


	Parser::~Parser()
	{
	}

	bool Parser::Parse(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		if (!scopes_.empty())
		{
			scopes_.clear();
		}
		// add global scope which is entirely disconnected from a scope and refers to anything not within a set of curly braces
		ScopingBlock global("Global");
		scopes_.push_back(global);
		
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
		
#ifdef SDIM_VERBOSE
		for (const auto& it : scopes_)
		{
			// newlines between scopes
			Utils::Log("");

			it.PrintScope();
		}
#endif
		
		Utils::Log("");
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
		// TODO: move all of these into functions to make this tidier
		if (Utils::IsOpeningBracket(next_token.token_type))
		{
			brackets_.push(next_token.token_type);
			if (next_token.token_type == TokenType::LeftBrace)
			{
				
				ScopingBlock anonymous_block(Utils::ConstructString("AnonymousScope", distribution_(*rng_)));
				scopes_.push_back(anonymous_block);
			}
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
			if (next_token.token_type == TokenType::RightBrace)
			{
				// close scope
				ScopingBlock closed_scope = scopes_.back();
				Utils::Log("Closed Scoping block ", closed_scope.GetName());
				scopes_.pop_back();
			}
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
				
				Token expect_left_brace = tokens[current_token + 2];
				if (expect_left_brace.token_type == TokenType::LeftBrace)
				{
					brackets_.push(expect_left_brace.token_type);
					// correctly formed module statement
					scopes_.push_back(ScopingBlock(expect_module_token.lexeme));
					// TODO: handle modules correctly
					Utils::Log("Found module: ", expect_module_token.lexeme);

					return ParseExpression(tokens, program_data, generator, current_token + 3);
				}
				else
				{
					Utils::Log("Malformed module declaration ", expect_module_token.lexeme);
					return ParseExpression(tokens, program_data, generator, current_token + 2);
				}
				
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
			ScopingBlock& current_scope = scopes_.back();
			// test against built in types
			for (UInt8 i = 0; i < Utils::VariableTypeToUInt8(VariableType::Unknown); i++)
			{
				if (next_token.lexeme == variable_type_strings[i])
				{
					Utils::Log("Found Type specifier for type: ", variable_type_strings[i]);

					Token expect_identifier_token = tokens[current_token + 1];

					if (expect_identifier_token.token_type == TokenType::Identifier)
					{
						// found identifier for type declaration good
						std::string var_name = expect_identifier_token.lexeme;

						Token expect_bracket_or_equal_token = tokens[current_token + 2];
						// TODO: process args
						if (expect_bracket_or_equal_token.token_type == TokenType::LeftBracket)
						{
							// function
							// add the left bracket to the bracket matching
							brackets_.push(expect_bracket_or_equal_token.token_type);

							size_t next_token_idx = 0;
							bool res = ParseFunctionDeclaration(tokens, program_data, generator, current_token + 3, static_cast<VariableType>(i), var_name, next_token_idx);
							if (!res)
							{
								// malformed function declaration
							}
							return ParseExpression(tokens, program_data, generator, next_token_idx);
						}
						else if (expect_bracket_or_equal_token.token_type == TokenType::Equal)
						{
							// var assignment
							// need to verify validity of assignment
							Utils::Log("Attempting declaration and assignment of ", var_name, " in scope ", current_scope.GetName());

							return ParseExpression(tokens, program_data, generator, current_token + 4);
						}
						else if (expect_bracket_or_equal_token.token_type == TokenType::SemiColon)
						{
							// just declaration without initialisation
							// ScopingBlock& current_scope = scopes_.back();
							Utils::Log("Attempting to add variable to scope ", current_scope.GetName());
							bool res = current_scope.AddVariable(var_name, SDIM::Variable(static_cast<VariableType>(i)));
							if (!res)
							{
								Utils::Log("Attempt to redeclare ", var_name);
							}
							Utils::Log("Added variable ", var_name, " to scope ", current_scope.GetName());
							return ParseExpression(tokens, program_data, generator, current_token + 3);
						}
						else
						{
							Utils::Log("Malformed variable or function definition ", var_name);
							// malformed
							return ParseExpression(tokens, program_data, generator, current_token + 1);
						}
					}
					// TODO: process type specifier for function and variable declarations
					return ParseExpression(tokens, program_data, generator, current_token + 1);
				}
			}
		}
		return ParseExpression(tokens, program_data, generator, ++current_token);
		// return true;
	}

	bool Parser::ParseFunctionDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator, UInt64 current_token, VariableType func_return, const std::string& func_name, size_t& next_token_idx)
	{
		(void)program_data;
		(void)generator;
		(void)func_return;
		
		// TODO: make this function handle function scope generating bytecode under a function
		// Is that even necessary because the bytecode for a function will be written after the function declaration is processed anyway

		// separate scopes for args and the function to allow redecleration of variables in function scope which exist in args scope
		// this pattern follows the way C++ does it, not in terms of scope naming however
		// the best part of this is the scope name doesn't even have to be unique so name collisions with other functions and modules are not an issue

		constexpr char* entrypoint_name = "Main";

		
		ScopingBlock func_args_scope(func_name + "__ARGS__");
		scopes_.push_back(func_args_scope);
		

		size_t current_consume_idx = current_token;
		while (current_consume_idx < tokens.size())
		{
			Token consume = tokens[current_consume_idx];
			if (consume.token_type == TokenType::RightBracket)
			{
				// end of args
				// pop args scope
				Utils::Log("Popping scope ", scopes_.back().GetName());
				scopes_.pop_back();

				brackets_.pop();
			}
			if (consume.token_type == TokenType::LeftBrace)
			{
				ScopingBlock func_scope(func_name);
				scopes_.push_back(func_scope);
				// start of function scope
				brackets_.push(consume.token_type);
				next_token_idx = current_consume_idx + 1;
				if (func_name == entrypoint_name)
				{
					Utils::Log("Function declaration for entrypoint ", entrypoint_name, " TODO write this to the header for the bytecode program so it starts in the right place");
					// TODO: adjust this to account for the header being written
					// IDEA: could have the header as a known size so the VM reads the header data and then the program is 0 indexed from the start of the program not the start of the program file
					size_t entrypoint_location = program_data.size();
					if (generator->GetType() == GeneratorType::BytecodeGenerator)
					{
						BytecodeHeader& header = static_cast<BytecodeGenerator*>(generator)->GetHeader();
						header.entrypoint_idx = entrypoint_location;
					}
				}
				return true;
			}

			current_consume_idx++;
		}
		next_token_idx = current_token + 1;
		return false;
	}

}