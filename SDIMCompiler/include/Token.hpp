#pragma once

#include <string>

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
		DoubleVerticalBar, LeftShift, RightShift,

		// Miscellaneous
		EOFToken, Identifier, NumericLiteral, StringLiteral, Unknown, Error
	};

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
		"DoubleVerticalBar", "LeftShift", "RightShift",

		// Miscellaneous
		"EOFToken", "Identifier", "NumericLiteral", "StringLiteral", "Unknown", "Error"
	};

	
	// TODO: Operator Precedence
	// Base operator precedence off of C++ to surprise users the least


	struct Token
	{
		TokenType token_type = TokenType::Unknown;

		std::string lexeme;

		Token(TokenType type, const std::string& lexeme_value) : token_type(type), lexeme(lexeme_value)
		{

		}

		std::string ToString() const;
	};

}