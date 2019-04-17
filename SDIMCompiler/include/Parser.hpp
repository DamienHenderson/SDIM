#pragma once

#include "Token.hpp"

#include <vector>
namespace SDIM
{
	class Parser
	{
	public:
		Parser();
		~Parser();

		// parses a program directly from a string
		bool Parse(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data);
		
	};
}
