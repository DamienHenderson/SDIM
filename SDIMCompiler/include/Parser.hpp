#pragma once

#include "Token.hpp"

#include <vector>

#include "Generator.hpp"
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
		bool ParseExpression(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data, Generator* generator);

		bool error_state_(false);
	};
}
