#pragma once

#include <string>

#include "Types.hpp"
namespace SDIM
{


	enum class TokenType
	{
		// Keywords
		If, Else, While, Do, True, False,
		Break, Return, Module, Include, For, Auto, 
		Null, Print, Class,

		// Single character symbols
		LeftBracket, RightBracket, LeftBrace, RightBrace, LeftSquareBracket, RightSquareBracket,
		LessThan, GreaterThan, SemiColon, Comma, Dot, Plus, Minus, Equal,
		ForwardSlash, Asterisk, Percent, Ampersand, VerticalBar, Caret, Bang, Tilde,

		// Multiple character symbols
		EqualEqual, BangEqual, TildeEqual, GreaterEqual, LessEqual, PlusEqual, MinusEqual, SlashEqual, AsteriskEqual,
		PercentEqual, AmpersandEqual, VerticalBarEqual, CaretEqual, DoubleAmpersand,
		DoubleVerticalBar, LeftShift, RightShift, PlusPlus, MinusMinus,

		// Miscellaneous
		EOFToken, Identifier, NumericLiteral, StringLiteral, Unknown, Error, Last
	};
	namespace Utils
	{
		UInt64 TokenTypeToUInt64(TokenType token_type);
		const char* TokenTypeToString(TokenType token_type);

		bool IsBracket(TokenType token_type);

		bool IsOpeningBracket(TokenType token_type);
		bool IsClosingBracket(TokenType token_type);

		bool IsMatchingBracketPair(TokenType opening, TokenType closing);
	}
	constexpr const char* token_type_strings[] =
	{

		"If", "Else", "While", "Do", "True", "False",
		"Break", "Return", "Module", "Include", "For", "Auto",
		"Null", "Print", "Class",


		"LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "LeftSquareBracket", "RightSquareBracket",
		"LessThan", "GreaterThan", "SemiColon", "Comma", "Dot", "Plus", "Minus", "Equal",
		"ForwardSlash", "Asterisk", "Percent", "Ampersand", "VerticalBar", "Caret", "Bang", "Tilde",

		// Multiple character symbols
		"EqualEqual", "BangEqual", "TildeEqual", "GreaterEqual", "LessEqual", "PlusEqual", "MinusEqual", "SlashEqual", "AsteriskEqual",
		"PercentEqual", "AmpersandEqual", "VerticalBarEqual", "CaretEqual", "DoubleAmpersand",
		"DoubleVerticalBar", "LeftShift", "RightShift", "PlusPlus", "MinusMinus",

		// Miscellaneous
		"EOFToken", "Identifier", "NumericLiteral", "StringLiteral", "Unknown", "Error", "Last"
	};

	



	struct Token
	{
		TokenType token_type = TokenType::Unknown;

		std::string lexeme;

		UInt64 line{ 0 }, col{ 0 };

		Token(TokenType type, const std::string& lexeme_value) : token_type(type), lexeme(lexeme_value)
		{

		}

		std::string ToString() const;

		// TODO: store line and column in tokens to make error messages from the compiler better
	};

}