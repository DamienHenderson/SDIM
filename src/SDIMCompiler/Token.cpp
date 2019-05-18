#include "Token.hpp"
namespace SDIM
{
	namespace Utils
	{
		UInt64 TokenTypeToUInt64(TokenType token_type)
		{
			return static_cast<UInt64>(token_type);
		}
		const char* TokenTypeToString(TokenType token_type)
		{
			return token_type_strings[TokenTypeToUInt64(token_type)];
		}
		bool IsBracket(TokenType token_type)
		{
			return token_type == TokenType::LeftBracket || token_type == TokenType::RightBracket || token_type == TokenType::LeftBrace || token_type == TokenType::RightBrace || token_type == TokenType::LeftSquareBracket || token_type == TokenType::RightSquareBracket;
		}
		bool IsOpeningBracket(TokenType token_type)
		{
			return token_type == TokenType::LeftBracket || token_type == TokenType::LeftBrace || token_type == TokenType::LeftSquareBracket;
		}
		bool IsClosingBracket(TokenType token_type)
		{
			return token_type == TokenType::RightBracket || token_type == TokenType::RightBrace || token_type == TokenType::RightSquareBracket;
		}
		bool IsMatchingBracketPair(TokenType opening, TokenType closing)
		{
			return (opening == TokenType::LeftBracket && closing == TokenType::RightBracket) || (opening == TokenType::LeftBrace && closing == TokenType::RightBrace) || (opening == TokenType::LeftSquareBracket && closing == TokenType::RightSquareBracket);
		}
	}
	std::string Token::ToString() const
	{
	std::string token_type_string = token_type_strings[static_cast<size_t>(token_type)];
	return token_type_string + ": " + lexeme;
	}
}
