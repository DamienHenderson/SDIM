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
		current_token = 0;
		return ParseModuleDeclaration(tokens, program_data, generator);
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

	bool Parser::ParseModuleDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		if (tokens[current_token].token_type != TokenType::Module)
		{
			Error(tokens[current_token], "Expected module keyword");
			return false;
		}
		// module so the following token should be an identifier
		Token expect_module_name_token = tokens[current_token + 1];
		if (expect_module_name_token.token_type == TokenType::Identifier)
		{

			Token expect_left_brace = tokens[current_token + 2];
			if (expect_left_brace.token_type == TokenType::LeftBrace)
			{
				brackets_.push(expect_left_brace.token_type);
				// correctly formed module statement
				scopes_.push_back(ScopingBlock(expect_module_name_token.lexeme));
				// TODO: handle modules correctly
				Utils::Log("Found module: ", expect_module_name_token.lexeme);

				// TODO: ParseTopLevelScope Function
				// Top level scopes should only contain functions
				return ParseExpression(tokens, program_data, generator);
			}
			else
			{
				Error(expect_module_name_token, "Expected { to open scoping block for module");
				return false;
			}

		}
		else
		{
			// Module names must be an identifier
			Error(expect_module_name_token, "Expected module name");
			return false;
		}
	}

	bool Parser::ParseExpression(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
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
		
		if (next_token.token_type == TokenType::NumericLiteral)
		{
			/*
			
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
			*/
			
			bool res = ParseNumericLiteral(tokens, program_data, generator);
			if (!res)
			{
				Utils::Log("Failed to parse numeric literal");
			}
			// return ParseExpression(tokens, program_data, generator, current_token + 1);
		}
		
		if (next_token.token_type == TokenType::Return)
		{
			// return
			// return will need to process an expression stopping at a semicolon
			// for now do it the hacky way
			// TODO: string returns?
			// TODO: return value in variable
			if (tokens[current_token + 1].token_type == TokenType::NumericLiteral && tokens[current_token + 2].token_type == TokenType::SemiColon)
			{
				Advance();
				bool res = ParseNumericLiteral(tokens, program_data, generator);
				if (!res)
				{
					Utils::Log("Failed to parse numeric literal following return statement");
				}
			}
			generator->WriteReturnInstruction(program_data);
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

							// size_t next_token_idx = 0;
							bool res = ParseFunctionDeclaration(tokens, program_data, generator, static_cast<VariableType>(i), var_name);
							if (!res)
							{
								// malformed function declaration
							}
							return ParseExpression(tokens, program_data, generator);
						}
						else if (expect_bracket_or_equal_token.token_type == TokenType::Equal)
						{
							// var assignment
							// need to verify validity of assignment
							Utils::Log("Attempting declaration and assignment of ", var_name, " in scope ", current_scope.GetName());
							// temporary
							current_token += 4;
							return ParseExpression(tokens, program_data, generator);
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


							switch (static_cast<VariableType>(i))
							{
							case VariableType::UInt8:
								generator->WritePushUInt8Instruction(program_data, 0);
								break;
							case VariableType::UInt16:
								generator->WritePushUInt16Instruction(program_data, 0);
								break;
							case VariableType::UInt32:
								generator->WritePushUInt32Instruction(program_data, 0);
								break;
							case VariableType::UInt64:
								generator->WritePushUInt64Instruction(program_data, 0);
								break;

							case VariableType::Int8:
								generator->WritePushInt8Instruction(program_data, 0);
								break;
							case VariableType::Int16:
								generator->WritePushInt16Instruction(program_data, 0);
								break;
							case VariableType::Int32:
								generator->WritePushInt32Instruction(program_data, 0);
								break;
							case VariableType::Int64:
								generator->WritePushInt64Instruction(program_data, 0);
								break;

							case VariableType::F32:
								generator->WritePushF32Instruction(program_data, 0.0f);
								break;
							case VariableType::F64:
								generator->WritePushF64Instruction(program_data, 0.0);
								break;
							default:
								break;
							}
							return ParseExpression(tokens, program_data, generator);
						}
						else
						{
							Utils::Log("Malformed variable or function definition ", var_name);
							// malformed
							return ParseExpression(tokens, program_data, generator);
						}
					}
					// TODO: process type specifier for function and variable declarations
					return ParseExpression(tokens, program_data, generator);
				}
			}
		}
		++current_token;
		return ParseExpression(tokens, program_data, generator);
		// return true;
	}

	
	bool Parser::ParseFunctionDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator, VariableType func_return, const std::string& func_name)
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

		Utils::Log("Function ", func_name, " defined at bytecode address ", program_data.size());

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
				// next_token_idx = current_consume_idx + 1;
				if (func_name == entrypoint_name)
				{
					Utils::Log("Function declaration for entrypoint ", entrypoint_name, " at bytecode address ", program_data.size());
					// TODO: adjust this to account for the header being written
					// IDEA: could have the header as a known size so the VM reads the header data and then the program is 0 indexed from the start of the program not the start of the program file
					size_t entrypoint_location = program_data.size();
					if (generator->GetType() == GeneratorType::BytecodeGenerator)
					{
						BytecodeHeader& header = static_cast<BytecodeGenerator*>(generator)->GetHeader();
						header.entrypoint_idx = entrypoint_location;
					}
					// temporary
					generator->WritePushStringInstruction(program_data, "Test String");
					generator->WriteCallInstruction(program_data, 0);
				}
				return true;
			}

			current_consume_idx++;
		}
		// next_token_idx = current_token + 1;
		return false;
	}

	bool Parser::ParseNumericLiteral(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		Token token = tokens[current_token];
		if (token.lexeme.find(".") != token.lexeme.npos)
		{
			if (token.lexeme.find("f") != token.lexeme.npos)
			{
				// 32 bit float
				F32 num = static_cast<F32>(std::atof(token.lexeme.c_str()));

				generator->WritePushF32Instruction(program_data, num);
			}
			else
			{
				// 64 bit float
				F64 num = std::atof(token.lexeme.c_str());

				generator->WritePushF64Instruction(program_data, num);
			}

		}
		else
		{
			// integer literal
			Int64 num = std::atoll(token.lexeme.c_str());
			generator->WritePushInt64Instruction(program_data, num);
		}
		return true;
	}

	bool Parser::ParseVariableDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;

		return false;
	}

	bool Parser::ParseAssignment(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;
		return false;
	}

	bool Parser::ParseGrouping(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		bool res = ParseExpression(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}
		bool close_bracket = MatchToken(tokens[current_token], TokenType::RightBracket);
		if (!close_bracket)
		{
			Error(tokens[current_token], "Expected closing right bracket in grouped expression");
			return false;
		}
		Advance();
		return true;
	}

	bool Parser::ParseUnary(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		TokenType op_type = tokens[current_token].token_type;
		// evaluate the rest of the expression the unary operator is operating on
		bool res = ParseExpression(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}

		if (op_type == TokenType::Minus)
		{
			generator->WriteNegateInstruction(program_data);
			return true;
		}
		else if (op_type == TokenType::MinusMinus)
		{
			generator->WritePushInt64Instruction(program_data, -1);
			generator->WriteSubtractInstruction(program_data);
			return true;
		}
		else if (op_type == TokenType::PlusPlus)
		{
			generator->WritePushUInt64Instruction(program_data, 1);
			generator->WriteAddInstruction(program_data);
			return true;
		}
		else
		{
			return false;
		}
		
	}

	bool Parser::ParseArithmetic(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		// parse all of the arithmetic operators in SDIM
		(void)tokens;
		(void)program_data;
		(void)generator;
		// (void)current_precedence;
		return false;
	}

	bool Parser::ConsumeToken(const std::vector<SDIM::Token>& tokens, TokenType expect, const char* error_message)
	{
		Token consume = tokens[current_token];
		if (consume.token_type == expect)
		{
			// handle brackets here
			// bool res = HandleBrackets(tokens);
			// if (!res)
			// {
			// 	return false;
			// }
			Advance();
			return true;
		}
		
		Error(tokens[current_token], error_message);
		
		return false;
	}
	/*
	bool Parser::HandleBrackets(const std::vector<SDIM::Token>& tokens)
	{
		
		Token token = tokens[current_token];
		if (Utils::IsOpeningBracket(token.token_type))
		{
			brackets_.push(token.token_type);
			
			return true;
		}
		else if (Utils::IsClosingBracket(token.token_type))
		{
			if (brackets_.empty())
			{
				Utils::Log("Closing bracket: ", token.lexeme, " found with no matching opening bracket");
				return false;
			}
			TokenType current_bracket = brackets_.top();

			if (!Utils::IsMatchingBracketPair(current_bracket, token.token_type))
			{
				Utils::Log("Expected matching bracket for ", Utils::TokenTypeToString(current_bracket), " but got ", Utils::TokenTypeToString(token.token_type), "Instead");
				return false;
			}
			Utils::Log("Matched opening bracket ", Utils::TokenTypeToString(current_bracket), " with ", Utils::TokenTypeToString(token.token_type));
			if (token.token_type == TokenType::RightBrace)
			{
				// close scope
				ScopingBlock closed_scope = scopes_.back();
				Utils::Log("Closed Scoping block ", closed_scope.GetName());
				scopes_.pop_back();
			}
			brackets_.pop();
		}
		return false;
	}
	*/
	bool Parser::MatchToken(const Token& token, TokenType expect)
	{
		return token.token_type == expect;
	}

	void Parser::Advance()
	{
		++current_token;
	}

	bool Parser::IsBuiltInType(const Token& token)
	{
		for (UInt8 i = 0; i < Utils::VariableTypeToUInt8(VariableType::Unknown); i++)
		{
			if (token.lexeme == variable_type_strings[i])
			{
				return true;
			}
		}
		return false;
	}

	void Parser::Error(const Token& at, const char* message)
	{
		
		Utils::Log("[ERROR] line(", at.line, "):column(", at.col, ") ", message);
	}

	VariableType Parser::TokenToVariableType(const Token& token)
	{
		for (UInt8 i = 0; i < Utils::VariableTypeToUInt8(VariableType::Unknown); i++)
		{
			if (token.lexeme == variable_type_strings[i])
			{
				return static_cast<VariableType>(i);
			}
		}
		return VariableType::Unknown;
	}

}