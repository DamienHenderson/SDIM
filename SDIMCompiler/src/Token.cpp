#include "Token.hpp"
namespace SDIM
{
	std::string Token::ToString() const
	{
	std::string token_type_string = token_type_strings[static_cast<size_t>(token_type)];
	return token_type_string + ": " + lexeme;
	}
}
