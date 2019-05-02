#include "Parser.hpp"

#include <Utils.hpp>

#include <random>
#include <unordered_map>

#include "BytecodeGenerator.hpp"

namespace SDIM
{
	Token GetToken(const std::vector<Token>& tokens, size_t idx)
	{
		if (idx >= tokens.size())
		{
			Utils::Log("Attempted to read past end of tokens");
			return Token(TokenType::Unknown, "");

		}
		return tokens[idx];
	}
	Parser::Parser()
	{
		rng_ = std::make_unique<std::default_random_engine>((std::random_device())());


	}


	Parser::~Parser()
	{
	}

	bool Parser::Parse(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
#ifdef SDIM_VERBOSE
		// for (const auto& token : tokens )
		// {
		//	Utils::Log(token.ToString());
		// }
#endif
		
		
		// Utilises pratt parsing 
		// inspired by this webpage http://journal.stuffwithstuff.com/2011/03/19/pratt-parsers-expression-parsing-made-easy/
		// also inspired by this webpage http://craftinginterpreters.com/compiling-expressions.html
		// also inspired by other sources 
		current_token = 0;
		bool res = ParseModuleDeclaration(tokens, program_data, generator);

		generator->WriteHaltInstruction(program_data);
		return res;
		
	}

	bool Parser::ParseModuleDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		Token expect_module_token = GetToken(tokens, current_token++);

		if (!MatchToken(expect_module_token, TokenType::Module))
		{
			Error(expect_module_token, "Expected module keyword");
			return false;
		}
		// module so the following token should be an identifier
		Token expect_module_name_token = GetToken(tokens, current_token++);
		if (MatchToken(expect_module_name_token, TokenType::Identifier))
		{

			Token expect_left_brace = GetToken(tokens, current_token++);
			if (MatchToken(expect_left_brace, TokenType::LeftBrace))
			{
				// brackets_.push(expect_left_brace.token_type);
				// correctly formed module statement
				// scopes_.push_back(ScopingBlock(expect_module_name_token.lexeme));
				// TODO: handle modules correctly
				Utils::Log("Found module: ", expect_module_name_token.lexeme);

				OpenScope();
				// TODO: ParseTopLevelScope Function
				// Top level scopes should only contain functions
				while (ParseFunctionDeclaration(tokens, program_data, generator))
				{

				}
				--current_token;
				CloseScope();
				return ConsumeToken(tokens, TokenType::RightBrace, "Expected } before EOF token");
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

		bool res = ParsePrecedence(tokens, program_data, generator, Precedence::Assignment);
		if (!res)
		{
			return false;
		}
		
		return true;

		// return ConsumeToken(tokens, TokenType::SemiColon, "Expected ;");

		/*
		/*
#ifdef SDIM_VERBOSE
		for (const auto& it : scopes_)
		{
			// newlines between scopes
			Utils::Log("");

			it.PrintScope();
		}
#endif

		Utils::Log("");
		if (GetToken(tokens, .empty())
		{
			Utils::Log("No GetToken(tokens,  found in compilation input");
			return false;
		}
		if (current_token >= GetToken(tokens, .size())
		{
			Utils::Log("Reached end of GetToken(tokens, ");
			return true;
		}
		Token next_token = GetToken(tokens, [current_token];
		Utils::Log("Parsing token ", next_token.ToString());
		// TODO: move all of these into functions to make this tidier

		if (next_token.token_type == TokenType::NumericLiteral)
		{

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
			if (GetToken(tokens, [current_token + 1].token_type == TokenType::NumericLiteral && GetToken(tokens, [current_token + 2].token_type == TokenType::SemiColon)
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

					Token expect_identifier_token = GetToken(tokens, [current_token + 1];

					if (expect_identifier_token.token_type == TokenType::Identifier)
					{
						// found identifier for type declaration good
						std::string var_name = expect_identifier_token.lexeme;

						Token expect_bracket_or_equal_token = GetToken(tokens, [current_token + 2];
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
		*/
	}


	bool Parser::ParseFunctionDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)program_data;
		(void)generator;
		if (current_token >= tokens.size())
		{
			Error(GetToken(tokens, tokens.size() - 1), "Reached end of file");
			return false;
		}
		Token expect_type = GetToken(tokens, current_token++);
		if (!MatchToken(expect_type, TokenType::Identifier))
		{
			Error(expect_type, "Expected type specifier for function declaration");
			return false;
		}
		VariableType func_return = TokenToVariableType(expect_type);
		if (func_return == VariableType::Unknown)
		{
			Error(expect_type, "Expected type specifier for function declaration");
			return false;
		}

		Token expect_func_name = GetToken(tokens, current_token++);
		if (!MatchToken(expect_type, TokenType::Identifier))
		{
			Error(expect_func_name, "Expected function name for function declaration");
			return false;
		}

		std::string func_name = expect_func_name.lexeme;
		Function func;
		func.name = func_name;
		for (const auto& it : funcs_)
		{
			if (it.name == func.name)
			{
				Error(expect_func_name, "Redefinition of previously defined function (SDIM does not currently support overloaded functions)");
				return false;
			}
		}
		func.addr = program_data.size();
		func.func_ret = func_return;

		funcs_.push_back(func);
		Utils::Log("Found func: ", func_name);
		// TODO: make this function handle function scope generating bytecode under a function
		// Is that even necessary because the bytecode for a function will be written after the function declaration is processed anyway

		// separate scopes for args and the function to allow redecleration of variables in function scope which exist in args scope
		// this pattern follows the way C++ does it, not in terms of scope naming however
		// the best part of this is the scope name doesn't even have to be unique so name collisions with other functions and modules are not an issue

		if (!ConsumeToken(tokens, TokenType::LeftBracket, "Expected left bracket for function declaration"))
		{
			return false;
		}
		// Parse args list here

		if (!ConsumeToken(tokens, TokenType::RightBracket, "Expected right bracket to close function args list declaration"))
		{
			return false;
		}
		constexpr char* entrypoint_name = "Main";

		Utils::Log("Function ", variable_type_strings[static_cast<UInt8>(func_return)], " ", func_name, " defined at bytecode address ", program_data.size());

		if (func_name == entrypoint_name)
		{
			// found main
			Utils::Log("Found entrypoint at: ", program_data.size());
			BytecodeGenerator* gen = (BytecodeGenerator*)generator;
			gen->GetHeader().entrypoint_idx = program_data.size();
		}
		// args scope
		OpenScope();
		// scopes_.push_back(func_args_scope);


		// handle args list

	

		ConsumeToken(tokens, TokenType::LeftBrace, "Expected opening brace for function scope");
		// func scope
		bool res = ParseBlock(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}
		
		ConsumeToken(tokens, TokenType::RightBrace, "Expected closing brace for function scope");
		// pop func scope
		// CloseScope();

		// pop args scope
		CloseScope();

		// next_token_idx = current_token + 1;
		return true;
	}

	bool Parser::ParseNumericLiteral(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		
		Token token = GetToken(tokens, current_token - 1);
		Utils::Log("Numeric literal: ", token.lexeme);
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

	bool Parser::ParseStringLiteral(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		Token expect_string = GetToken(tokens, current_token - 1);
		if (!MatchToken(expect_string, TokenType::StringLiteral))
		{
			Error(expect_string, "Expected string literal");
			return false;
		}
		generator->WritePushStringInstruction(program_data, expect_string.lexeme.c_str());
		// Advance();
		return true;
	}
	/*
	bool Parser::ParseVariableDeclaration(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;

		return false;
	}
	*/
	bool Parser::ParseAssignment(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;

		// TODO: handle assignment
		bool res = ParseExpression(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}
		return true;
	}

	bool Parser::ParseGrouping(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		bool res = ParseExpression(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}
		bool close_bracket = MatchToken(GetToken(tokens, current_token), TokenType::RightBracket);
		if (!close_bracket)
		{
			Error(GetToken(tokens, current_token), "Expected closing right bracket in grouped expression");
			return false;
		}
		Advance();
		return true;
	}

	bool Parser::ParseUnary(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		TokenType op_type = GetToken(tokens, current_token - 1).token_type;
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

	bool Parser::ParsePrecedence(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator, Precedence current_precedence)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;
		(void)current_precedence;

		// handle prefix expressions
		// if(GetToken(tokens, [current_token])
		Token prev = GetToken(tokens, current_token);
		Advance();
		ParseFunc prefix_func = GetParseRule(prev.token_type).prefix;
		if (prefix_func == nullptr)
		{
			Error(prev, "Expected prefix expression");
			return false;
		}

		bool res = prefix_func(this, tokens, program_data, generator);
		if (!res)
		{
			Error(prev, "Expected prefix expression");
			return false;
		}
		while (current_precedence <= GetParseRule(GetToken(tokens, current_token).token_type).prec)
		{
			Advance();
			ParseFunc infix_func = GetParseRule(GetToken(tokens, current_token - 1).token_type).infix;
			// if (infix_func == nullptr)
			// {
			// 	Error(GetToken(tokens, current_token), "Expression is not a valid infix expression");
			// 	return false;
			// }
			infix_func(this, tokens, program_data, generator);

		}
		return true;
	}

	bool Parser::ParseReturn(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		Token op = GetToken(tokens, current_token - 1);
		if (op.token_type != TokenType::Return)
		{
			Error(op, "Expected return keyword");
		}
		// parse operators with higher precedence
		bool res = ParseExpression(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}
		generator->WriteReturnInstruction(program_data);

		return true;
	}

	bool Parser::ParseBlock(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;
		OpenScope();
		while (!MatchToken(tokens[current_token], TokenType::RightBrace) && !MatchToken(tokens[current_token], TokenType::EOFToken))
		{
			bool res = ParseDeclaration(tokens, program_data, generator);
			if (!res)
			{
				return false;
			}
		}
		ConsumeToken(tokens, TokenType::RightBrace, "Expected closing brace for scoping block");
		CloseScope();
		return true;
	}

	bool Parser::ParseDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		if (MatchToken(GetToken(tokens, current_token), TokenType::Identifier)) 
		{
			// declaration
			Token expect_type = GetToken(tokens, current_token);
			if (IsBuiltInType(expect_type))
			{
				bool res = DeclareVariable(tokens, program_data, generator);
				if (!res)
				{
					return false;
				}
				return ConsumeToken(tokens, TokenType::SemiColon, "expect ; at end of declaration");
			}
			else
			{
				return ParseStatement(tokens, program_data, generator);
			}
		}
		else 
		{
			// statement
			return ParseStatement(tokens, program_data, generator);
		}
		// return false;
	}

	bool Parser::ParseStatement(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;
		Utils::Log("Statement");
		Token curr = GetToken(tokens, current_token);
		Advance();
		if (MatchToken(curr, TokenType::Return))
		{
			return ParseReturn(tokens, program_data, generator);
		}
		else if (MatchToken(curr, TokenType::Print))
		{
			return ParsePrint(tokens, program_data, generator);
		}
		else if (MatchToken(curr, TokenType::Identifier))
		{
			// return ParseIdentifier()
		}
		return false;
	}

	bool Parser::ParseIdentifier(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;
		Token expect_type_or_identifier = GetToken(tokens, current_token - 1);
		if (IsBuiltInType(expect_type_or_identifier))
		{
			Utils::Log("Found type specifier ", expect_type_or_identifier.lexeme);
			// var declaration
			Token expect_var_name = GetToken(tokens, current_token);
			if (!MatchToken(expect_var_name, TokenType::Identifier))
			{
				Error(expect_var_name, "Expected Identifier in variable declaration");
				return false;
			}
			Token next_token = GetToken(tokens, current_token + 1);
			if (MatchToken(next_token, TokenType::SemiColon))
			{
				// ScopingBlock current_scope = scopes_.back();

				// just declaration
				LocalVar var;
				var.var = Variable(TokenToVariableType(expect_type_or_identifier));
				generator->WriteLocalVarInstruction(program_data, locals_.size());
				var.scope = scope_idx_;
				locals_.push_back(var);
				
			}
			bool res = ParsePrecedence(tokens, program_data, generator, Precedence::Assignment);
			if (!res)
			{
				return false;
			}
			
		}
		else if(expect_type_or_identifier.token_type == TokenType::Identifier)
		{
			Utils::Log("Found identifier ", expect_type_or_identifier.lexeme);
			
			// generator->WritePushLocalInstruction(program_data, it->second);
			bool res = ParseExpression(tokens, program_data, generator);
			if (!res)
			{
				return false;
			}
		}
		return true;
	}

	bool Parser::BinaryExpression(const std::vector<SDIM::Token> & tokens, std::vector<unsigned char> & program_data, Generator * generator)
	{
		
		Token op = GetToken(tokens, current_token - 1);

		// parse operators with higher precedence
		bool res = ParsePrecedence(tokens, program_data, generator, GetPrecedence(op.token_type));
		if (!res)
		{
			return false;
		}

		Utils::Log("Wrote instruction for binary operator ", Utils::TokenTypeToString(op.token_type));
		switch (op.token_type)
		{
			// arithmetic
		case TokenType::Plus:
			generator->WriteAddInstruction(program_data);
			Utils::Log("Wrote add instruction");
			return true;
		case TokenType::Minus:
			generator->WriteSubtractInstruction(program_data);
			return true;
		case TokenType::Asterisk:
			generator->WriteMultiplyInstruction(program_data);
			return true;
		case TokenType::ForwardSlash:
			generator->WriteDivideInstruction(program_data);
			return true;
		case TokenType::Percent:
			generator->WriteModuloInstruction(program_data);
			return true;
		case TokenType::Ampersand:
			generator->WriteAndInstruction(program_data);
			return true;
		case TokenType::VerticalBar:
			generator->WriteOrInstruction(program_data);
			return true;
		case TokenType::Caret:
			generator->WriteXorInstruction(program_data);
			return true;
			//logical
		case TokenType::EqualEqual:
			generator->WriteEqualInstruction(program_data);
			return true;
		case TokenType::BangEqual:
			generator->WriteNotEqualInstruction(program_data);
			return true;
		case TokenType::Bang:
			generator->WriteNotInstruction(program_data);
			return true;
			// relational
		case TokenType::LessThan:
			generator->WriteLessInstruction(program_data);
			return true;
		case TokenType::LessEqual:
			generator->WriteLessEqualInstruction(program_data);
			return true;
		case TokenType::GreaterThan:
			generator->WriteGreaterInstruction(program_data);
			return true;
		case TokenType::GreaterEqual:
			generator->WriteGreaterEqualInstruction(program_data);
			return true;
			//case TokenType::Tilde:
			//	generator->WriteBitwiseNotInstruction(program_data);


		default:
			Error(op, "Expected binary operator");
			return false;
		}
		return false;
	}

	bool Parser::DeclareVariable(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		Token type_token = GetToken(tokens, current_token);

		VariableType var_type = TokenToVariableType(type_token);

		Advance();
		Token name_token = GetToken(tokens, current_token);

		Advance();

		Token expect_equal_or_semicolon = GetToken(tokens, current_token);

		if (MatchToken(expect_equal_or_semicolon, TokenType::Equal))
		{
			Advance();
			ParseExpression(tokens, program_data, generator);
			

		}
		else
		{
			// TODO: do this properly based on the type of the variable being declared
			generator->WritePushInt64Instruction(program_data, 0);
		}
		LocalVar local_var;
		local_var.var.type = var_type;
		local_var.name = name_token.lexeme;
		local_var.scope = scope_idx_;
		local_var.local_idx = locals_.size();
		// check for name conflicts
		if (AddLocal(local_var))
		{
			locals_.push_back(local_var);
			
			Utils::Log("Added local var ", variable_type_strings[static_cast<UInt8>(local_var.var.type)], " ", local_var.name);
			generator->WriteLocalVarInstruction(program_data, locals_.size());
			// ConsumeToken(tokens, TokenType::SemiColon, "Expected ; at end of variable declaration");
			return true;
		}
		return false;
	}

	bool Parser::ParsePrint(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		Token print = GetToken(tokens, current_token - 1);

		if (!MatchToken(print, TokenType::Print))
		{
			Error(print, "Expected print statement");
			return false;
		}
		bool res = ParseExpression(tokens, program_data, generator);
		if (!res)
		{
			return false;
		}
		return ConsumeToken(tokens, TokenType::SemiColon, "Expected semicolon to end print statement");
	}

	bool Parser::ExpressionStatement(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator)
	{
		(void)tokens;
		(void)program_data;
		(void)generator;
		return false;
	}

	void Parser::OpenScope()
	{
		++scope_idx_;
	}

	void Parser::CloseScope()
	{
		--scope_idx_;
		if (locals_.empty())
		{
			return;
		}
		for (auto it = locals_.begin(); it != locals_.end();)
		{
			if (it->scope > scope_idx_)
			{
				it = locals_.erase(it);
			}
			else
			{
				++it;
			}
		}

	}



	bool Parser::ConsumeToken(const std::vector<SDIM::Token> & tokens, TokenType expect, const char* error_message)
	{
		Token consume = GetToken(tokens, current_token);
		if (consume.token_type == expect)
		{
			// handle brackets here
			// bool res = HandleBrackets(GetToken(tokens, );
			// if (!res)
			// {
			// 	return false;
			// }
			Advance();
			return true;
		}

		Error(GetToken(tokens, current_token), error_message);

		return false;
	}
	/*
	bool Parser::HandleBrackets(const std::vector<SDIM::Token>& GetToken(tokens, )
	{

		Token token = GetToken(tokens, [current_token];
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
	bool Parser::MatchToken(const Token & token, TokenType expect)
	{
		return token.token_type == expect;
	}

	bool Parser::AddLocal(const LocalVar& local)
	{
		for (auto it = locals_.begin(); it != locals_.end(); it++)
		{
			if (it->scope == local.scope && it->name == local.name)
			{
				// var exists in same scope
				return false;
			}
		}
		return true;
	}

	void Parser::Advance()
	{
		++current_token;
	}

	bool Parser::IsBuiltInType(const Token & token)
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

	void Parser::Error(const Token & at, const char* message)
	{

		Utils::Log("[ERROR] line(", at.line, "):column(", at.col, ") near ", at.lexeme, ": ", message);
	}

	VariableType Parser::TokenToVariableType(const Token & token)
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
	// make it quicker to type parser rules
#define DefParseRule(token, prefix, infix) {token, {infix, prefix, GetPrecedence(token)}}
	ParseRule Parser::GetParseRule(TokenType token)
	{
		static const std::unordered_map<TokenType, ParseRule> parse_rules =
		{
			// brackets
			DefParseRule(TokenType::LeftBracket, &Parser::ParseGrouping, nullptr),
			// {TokenType::LeftBracket, {nullptr, &Parser::ParseGrouping, GetPrecedence(TokenType::LeftBracket)} },
			// arithmetic
			DefParseRule(TokenType::PlusPlus, &Parser::ParseUnary, nullptr),
			DefParseRule(TokenType::MinusMinus, &Parser::ParseUnary, nullptr),
			DefParseRule(TokenType::Minus, &Parser::ParseUnary, &Parser::BinaryExpression),
			DefParseRule(TokenType::Plus, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::Asterisk, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::ForwardSlash, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::Percent, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::Ampersand, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::VerticalBar, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::Caret, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::Tilde, &Parser::ParseUnary, nullptr),
			// logical
			DefParseRule(TokenType::EqualEqual, &Parser::ParseUnary, nullptr),
			DefParseRule(TokenType::BangEqual, &Parser::ParseUnary, nullptr),
			DefParseRule(TokenType::GreaterThan, &Parser::ParseUnary, &Parser::BinaryExpression),
			DefParseRule(TokenType::LessThan, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::GreaterEqual, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::LessEqual, nullptr, &Parser::BinaryExpression),
			DefParseRule(TokenType::Bang, &Parser::ParseUnary, nullptr),
			// literals
			DefParseRule(TokenType::StringLiteral, &Parser::ParseStringLiteral, nullptr),
			DefParseRule(TokenType::NumericLiteral, &Parser::ParseNumericLiteral, nullptr),

			// Assignment
			DefParseRule(TokenType::Equal, nullptr, &Parser::ParseAssignment),
			// semicolon
			DefParseRule(TokenType::SemiColon, nullptr, nullptr),

			// return
			DefParseRule(TokenType::Return, &Parser::ParseReturn, nullptr),

			// variables and types
			DefParseRule(TokenType::Identifier, &Parser::ParseIdentifier, nullptr)
		};
		const auto& it = parse_rules.find(token);
		if(it == parse_rules.cend())
		{
			return ParseRule{ nullptr, nullptr, Precedence::None };
		}
		return it->second;
	}

}