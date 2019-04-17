#include "Parser.hpp"

#include <Utils.hpp>
namespace SDIM
{

	Parser::Parser()
	{
	}


	Parser::~Parser()
	{
	}

	bool Parser::Parse(const std::vector<SDIM::Token>& tokens, std::vector<unsigned char>& program_data)
	{
		(void)program_data;
		for (size_t idx = 0; idx < tokens.size(); ++idx)
		{
			Token current_token = tokens[idx];

			SDIM::Utils::Log("Token[", idx, "]: ", current_token.ToString(), "\n");
		}
		return false;
	}

}