#include "Scanner.hpp"

#include "LangUtils.hpp"

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
		for (size_t i = 0; i < file_contents.length(); i++)
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
				// whitespace ends numeric literals and identifiers
				if (current_token.token_type == TokenType::Identifier || current_token.token_type == TokenType::NumericLiteral)
				{
					// TODO: make this better using a radix tree
					auto CheckKeyword = [&current_token](const std::string& match, TokenType type_on_match) -> void
					{
						LogString("Tested: " + current_token.lexeme +" against keyword: " + match);
						if (current_token.lexeme == match)
						{
							LogString("Matched Keyword: " + match);
							current_token.token_type = type_on_match;
						}
					};
					// check if it matches keywords
					CheckKeyword("if", TokenType::If);
					CheckKeyword("else", TokenType::Else);
					CheckKeyword("while", TokenType::While);
					CheckKeyword("do", TokenType::Do);
					CheckKeyword("true", TokenType::True);
					CheckKeyword("false", TokenType::False);
					CheckKeyword("break", TokenType::Break);
					CheckKeyword("return", TokenType::Return);
					CheckKeyword("module", TokenType::Module);
					CheckKeyword("include", TokenType::Include);
					CheckKeyword("for", TokenType::For);
					CheckKeyword("auto", TokenType::Auto);
					CheckKeyword("null", TokenType::Null);
					CheckKeyword("print", TokenType::Print);
					CheckKeyword("class", TokenType::Class);
					


					std::cout << "Extracted lexeme: " << current_token.lexeme << "\n";
					tokens.push_back(current_token);
					current_token = Token(TokenType::Unknown, "");
				}
				// skip whitespace
				continue;
			}
			if (current_token.token_type == TokenType::Identifier && !IsIdentifier(current_char))
			{
				// TODO: make this better using a radix tree
				auto CheckKeyword = [&current_token](const std::string& match, TokenType type_on_match) -> void
				{
					LogString("Tested: " + current_token.lexeme + " against keyword: " + match);
					if (current_token.lexeme == match)
					{
						LogString("Matched Keyword: " + match);
						current_token.token_type = type_on_match;
					}
				};
				// check if it matches keywords
				CheckKeyword("if", TokenType::If);
				CheckKeyword("else", TokenType::Else);
				CheckKeyword("while", TokenType::While);
				CheckKeyword("do", TokenType::Do);
				CheckKeyword("true", TokenType::True);
				CheckKeyword("false", TokenType::False);
				CheckKeyword("break", TokenType::Break);
				CheckKeyword("return", TokenType::Return);
				CheckKeyword("module", TokenType::Module);
				CheckKeyword("include", TokenType::Include);
				CheckKeyword("for", TokenType::For);
				CheckKeyword("auto", TokenType::Auto);
				CheckKeyword("null", TokenType::Null);
				CheckKeyword("print", TokenType::Print);
				CheckKeyword("class", TokenType::Class);

				tokens.push_back(current_token);
				std::cout << "Extracted lexeme: " << current_token.lexeme << "\n";

				current_token = Token(TokenType::Unknown, "");

			}
			if (current_token.token_type == TokenType::NumericLiteral && !std::isdigit(current_char))
			{
				tokens.push_back(current_token);
				std::cout << "Extracted lexeme: " << current_token.lexeme << "\n";
				current_token = Token(TokenType::Unknown, "");
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
				if (MatchNext('<', i + 1))
				{
					tokens.push_back(Token(TokenType::LeftShift, "<<"));
					++i;
					LogString("Extracted lexeme: <<");
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
				if (MatchNext('>', i + 1))
				{
					tokens.push_back(Token(TokenType::RightShift, ">>"));
					++i;
					LogString("Extracted lexeme: >>");
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
			case '=':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(Token(TokenType::EqualEqual, "="));
					++i;
					LogString("Extracted lexeme: ==");
				}
				else
				{
					Token(TokenType::Equal, ConvertToString(current_char));
					LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '"':
				if (current_token.token_type == TokenType::StringLiteral)
				{
					// if the current lexeme is a string literal then a quote will finish it
					// note that a preceding backslash will escape a string literal
					if (i > 0 && file_contents[i - 1] == '\\')
					{
						// escape char here
						current_token.lexeme += current_char;
					}
					else
					{
						tokens.push_back(current_token);
						LogString("Extracted lexeme: " + current_token.lexeme);
						current_token = Token(TokenType::Unknown, "");
					}

				}
				else
				{
					current_token.token_type = TokenType::StringLiteral;
					
				}
				break;
			
			default:
				// TODO: remove once keywords and identifiers are processed
				// LogString(std::string("Unknown char: ") + current_char);
				if (current_token.token_type == TokenType::StringLiteral)
				{
					current_token.lexeme += current_char;
				}
				else if (current_token.token_type == TokenType::Identifier && IsIdentifier(current_char))
				{
					current_token.lexeme += current_char;
				}
				else if(current_token.token_type == TokenType::Unknown && IsIdentifierStart(current_char))
				{
					current_token.token_type = TokenType::Identifier;
					current_token.lexeme += current_char;
				}
				else if (std::isdigit(current_char))
				{
					if (current_token.token_type == TokenType::Unknown)
					{
						current_token.token_type = TokenType::NumericLiteral;
						current_token.lexeme += current_char;
					}
					else if (current_token.token_type == TokenType::NumericLiteral)
					{
						current_token.lexeme += current_char;
					}
				}
				break;
			}
		}
		
		// TODO: keywords
		// TODO: identifiers (types and variables)
		// TODO: literals
		return true;
	}

}