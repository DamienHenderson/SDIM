#pragma once

#include "Token.hpp"

#include <vector>
#include <stack>
#include <random>
#include <memory>

#include "Generator.hpp"
#include "ScopingBlock.hpp"
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
		bool ParseExpression(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator, UInt64 current_token);

		bool ParseFunctionDeclaration(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator, UInt64 current_token, VariableType func_return, const std::string& func_name, size_t& next_token_idx);

		// bool error_state_{ false };
		
		// used for bracket matching
		std::stack<TokenType> brackets_;

		std::vector<ScopingBlock> scopes_;

		
		std::unique_ptr<std::default_random_engine> rng_{ nullptr };

		std::uniform_int_distribution<UInt64> distribution_;
	};
}
