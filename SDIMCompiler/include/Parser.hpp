#pragma once

#include "Token.hpp"

#include <vector>
#include <stack>
#include <random>
#include <memory>

#include "Generator.hpp"
#include "ScopingBlock.hpp"
#include "Stack.hpp"

namespace SDIM
{
	
	class Parser
	{
	public:
		Parser();
		~Parser();

		// parses a sequence of tokens into a complete bytecode program
		bool Parse(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);
	private:
		
		bool ParseModuleDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);

		bool ParseExpression(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);


		bool ParseFunctionDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator, VariableType func_return, const std::string& func_name);

		bool ParseNumericLiteral(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);
		
		bool ParseVariableDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);

		bool ParseAssignment(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);
		
		/// Parse brackets but not square brackets or braces
		bool ParseGrouping(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);

		bool ParseUnary(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);

		bool ParseArithmetic(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);
		// bool error_state_{ false };
		
		// used for bracket matching
		std::stack<TokenType> brackets_;

		std::vector<ScopingBlock> scopes_;

		// Used to 
		// Stack var_stack_;
		
		
		std::unique_ptr<std::default_random_engine> rng_{ nullptr };

		std::uniform_int_distribution<UInt64> distribution_;

		
		bool ConsumeToken(const std::vector<SDIM::Token>& tokens, TokenType expect, const char* error_message);

		// bool HandleBrackets(const std::vector<SDIM::Token>& tokens);

		bool MatchToken(const Token& token, TokenType expect);

		void Advance();

		bool IsBuiltInType(const Token& token);

		void Error(const Token& at, const char* message);

		VariableType TokenToVariableType(const Token& token);

		UInt64 current_token{ 0 };
	};
}