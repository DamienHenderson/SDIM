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
		
		auto MatchNext = [](const std::string& program_string, char match, size_t idx) -> bool
		{
			return program_string[idx] == match;
		};
		
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
				tokens.push_back(Token(TokenType::LessThan, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '>':
				tokens.push_back(Token(TokenType::GreaterThan, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
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
				tokens.push_back(Token(TokenType::Minus, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '+':
				tokens.push_back(Token(TokenType::Plus, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '/':
				tokens.push_back(Token(TokenType::ForwardSlash, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '*':
				tokens.push_back(Token(TokenType::Asterisk, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '%':
				tokens.push_back(Token(TokenType::Percent, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '&':
				tokens.push_back(Token(TokenType::Ampersand, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '|':
				tokens.push_back(Token(TokenType::VerticalBar, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '^':
				tokens.push_back(Token(TokenType::Caret, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '!':
				tokens.push_back(Token(TokenType::Bang, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '~':
				tokens.push_back(Token(TokenType::Tilde, ConvertToString(current_char)));
				LogString(std::string("Extracted lexeme: ") + current_char);
				break;
				 
			default:
				LogString(std::string("Unknown char: ") + current_char);
				break;
			}
		}

		return true;
	}

}