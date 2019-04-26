#include "Token.hpp"
namespace SDIM
{
	namespace Utils
	{
		UInt64 TokenTypeToUInt64(TokenType token_type)
		{
			return static_cast<UInt64>(token_type);
		}
	}
	std::string Token::ToString() const
	{
	std::string token_type_string = token_type_strings[static_cast<size_t>(token_type)];
	return token_type_string + ": " + lexeme;
	}
}
