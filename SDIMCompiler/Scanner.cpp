#include "Scanner.hpp"

#include "Utils.hpp"

// temp
#include <iostream>
namespace SDIM
{
	Scanner::Scanner()
	{
	}


	Scanner::~Scanner()
	{
	}

	bool Scanner::ScanFile(const std::string & path, std::vector<Token>& tokens)
	{
		std::string file_contents = ReadWholeFile(path);
		std::cout << file_contents << "\n";
		
		auto MatchNext = [&file_contents](char match, size_t idx) -> bool
		{
			return file_contents[idx] == match;
		};
		// for keywords, identifiers and literals which may encompass several characters
		Token current_token(TokenType::Unknown,"");
		for (auto i = 0; i < file_contents.length(); i++)
		{
			char current_char = file_contents[i];
			if (current_char == '\0')
			{
				// EOF
				// emit compile error here if the eof is premature (not implemented yet)
				
				
				tokens.push_back(Token(TokenType::EOFToken, ConvertToString(current_char)));
				break;
			}
			// String literals may contain whitespace
			if (IsWhitespace(current_char) && current_token.token_type != TokenType::StringLiteral)
			{
				// skip whitespace
				continue;
			}
			switch (current_char)
			{
			case '(':
				tokens.push_back(Token(TokenType::LeftBracket, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case ')':
				tokens.push_back(Token(TokenType::RightBracket, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '{':
				tokens.push_back(Token(TokenType::LeftBrace, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '}':
				tokens.push_back(Token(TokenType::RightBrace, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '[':
				tokens.push_back(Token(TokenType::LeftSquareBracket, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case ']':
				tokens.push_back(Token(TokenType::RightSquareBracket, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '<':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::LessEqual, "<="));
					++i;
					LogString("Extracted lexeme: <=");
				}
				else
				{
					Token(TokenType::LessThan, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '>':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::GreaterEqual, ">="));
					++i;
					LogString("Extracted lexeme: >=");
				}
				else
				{
					Token(TokenType::GreaterThan, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case ';':
				tokens.push_back(Token(TokenType::SemiColon, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case ',':
				tokens.push_back(Token(TokenType::Comma, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '.':
				tokens.push_back(Token(TokenType::Dot, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '-':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::MinusEqual, "-="));
					++i;
					LogString("Extracted lexeme: -=");
				}
				else
				{
					Token(TokenType::Minus, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '+':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::PlusEqual, "+="));
					++i;
					LogString("Extracted lexeme: +=");
				}
				else
				{
					Token(TokenType::Plus, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '/':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::SlashEqual, "/="));
					++i;
					LogString("Extracted lexeme: /=");
				}
				else
				{
					Token(TokenType::ForwardSlash, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '*':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::AsteriskEqual, "*="));
					++i;
					LogString("Extracted lexeme: *=");
				}
				else
				{
					Token(TokenType::Asterisk, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '%':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::PercentEqual, "%="));
					++i;
					LogString("Extracted lexeme: %=");
				}
				else
				{
					Token(TokenType::Percent, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '&':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::AmpersandEqual, "&="));
					++i;
					LogString("Extracted lexeme: &=");
				}
				else if (MatchNext('|', i + 1))
				{
					tokens.push_back(Token(TokenType::DoubleAmpersand, "&&"));
					++i;
					LogString("Extracted lexeme: &&");
				}
				else
				{
					Token(TokenType::VerticalBar, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '|':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::VerticalBarEqual, "|="));
					++i;
					LogString("Extracted lexeme: |=");
				}
				else if (MatchNext('|', i + 1))
				{
					tokens.push_back(Token(TokenType::DoubleVerticalBar, "||"));
					++i;
					LogString("Extracted lexeme: ||");
				}
				else
				{
					Token(TokenType::VerticalBar, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '^':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::CaretEqual, "^="));
					++i;
					LogString("Extracted lexeme: ^=");
				}
				else
				{
					Token(TokenType::Caret, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '!':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::BangEqual, "!="));
					++i;
					LogString("Extracted lexeme: !=");
				}
				else
				{
					Token(TokenType::Bang, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '~':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::TildeEqual, "~="));
					++i;
					LogString("Extracted lexeme: ~=");
				}
				else
				{
					Token(TokenType::Tilde, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
				 
			default:
				// TODO: remove once keywords and identifiers are processed
				LogString(std::string("Unknown char: ") + current_char);
				break;
			}
		}
		// TODO: keywords
		// TODO: identifiers (types and variables)
		// TODO: literals
		return true;
	}

}