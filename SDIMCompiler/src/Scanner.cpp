#include "Scanner.hpp"

#include "LangUtils.hpp"

#include "Utils.hpp"
namespace SDIM
{
	Scanner::Scanner()
	{
	}


	Scanner::~Scanner()
	{
	}

	bool Scanner::ScanString(const std::string& program, std::vector<Token>& tokens)
	{
		
		std::string prog_string = program;
		auto MatchNext = [&prog_string](char match, size_t idx) -> bool
		{
			return prog_string[idx] == match;
		};
		auto AddToken = [this](std::vector<Token> & token_vec, const Token& token) -> Token
		{
#ifdef SDIM_VERBOSE
			Utils::Log("Added token ", token.ToString());
#endif
			
			token_vec.push_back(token);

			return Token(TokenType::Unknown, "");
		};
		// for keywords, identifiers and literals which may encompass several characters
		Token current_token(TokenType::Unknown, "");
		for (size_t i = 0; i < program.length(); i++)
		{

			char current_char = prog_string[i];
			++col_;
			if (current_char == '\0')
			{
				// EOF
				// emit compile error here if the eof is premature (not implemented yet)


				tokens.push_back(CreateToken(TokenType::EOFToken, ConvertToString(current_char)));
				break;
			}
			// String literals may contain whitespace
			if (IsWhitespace(current_char) && current_token.token_type != TokenType::StringLiteral)
			{
				// whitespace ends numeric literals and identifiers
				if (current_token.token_type == TokenType::Identifier)
				{
					// TODO: make this better using a radix tree
					auto CheckKeyword = [&current_token](const std::string & match, TokenType type_on_match) -> void
					{
						LogString("Tested: " + current_token.lexeme + " against keyword: " + match);
						if (current_token.lexeme == match)
						{
							// LogString("Matched Keyword: " + match);
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



					// std::cout << "Extracted lexeme: " << current_token.lexeme << "\n";
					current_token = AddToken(tokens, current_token);
				}
				// skip whitespace
				if (current_char == '\n')
				{
					++line_;
					col_ = 0;
				}
				continue;
			}
			if (current_token.token_type == TokenType::Identifier && !IsIdentifier(current_char))
			{
				// TODO: make this better using a radix tree
				auto CheckKeyword = [&current_token](const std::string & match, TokenType type_on_match) -> void
				{
					LogString("Tested: " + current_token.lexeme + " against keyword: " + match);
					if (current_token.lexeme == match)
					{
						// LogString("Matched Keyword: " + match);
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

				current_token = AddToken(tokens, current_token);
				// continue;

			}
			if (current_token.token_type == TokenType::NumericLiteral && !std::isdigit(current_char) && current_char != '.' && current_char != 'f')
			{
				current_token = AddToken(tokens, current_token);
				
			}
			switch (current_char)
			{
			case '(':
				current_token = AddToken(tokens, CreateToken(TokenType::LeftBracket, ConvertToString(current_char)));
				
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case ')':
				tokens.push_back(CreateToken(TokenType::RightBracket, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '{':
				tokens.push_back(CreateToken(TokenType::LeftBrace, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '}':
				tokens.push_back(CreateToken(TokenType::RightBrace, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '[':
				tokens.push_back(CreateToken(TokenType::LeftSquareBracket, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case ']':
				tokens.push_back(CreateToken(TokenType::RightSquareBracket, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '<':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::LessEqual, "<="));
					++i;
					// LogString("Extracted lexeme: <=");
				}
				if (MatchNext('<', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::LeftShift, "<<"));
					++i;
					// LogString("Extracted lexeme: <<");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::LessThan, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '>':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::GreaterEqual, ">="));
					++i;
					// LogString("Extracted lexeme: >=");
				}
				if (MatchNext('>', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::RightShift, ">>"));
					++i;
					// LogString("Extracted lexeme: >>");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::GreaterThan, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case ';':
				tokens.push_back(CreateToken(TokenType::SemiColon, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case ',':
				tokens.push_back(CreateToken(TokenType::Comma, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '.':
				if (current_token.token_type == TokenType::NumericLiteral)
				{
					current_token.lexeme += current_char;
					break;
				}
				tokens.push_back(CreateToken(TokenType::Dot, ConvertToString(current_char)));
				// LogString(std::string("Extracted lexeme: ") + current_char);
				break;
			case '-':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::MinusEqual, "-="));
					++i;
					// LogString("Extracted lexeme: -=");
				}
				if (MatchNext('-', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::MinusMinus, "--"));
					++i;
					// LogString("Extracted lexeme: +=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Minus, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '+':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::PlusEqual, "+="));
					++i;
					// LogString("Extracted lexeme: +=");
				}
				if (MatchNext('+', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::PlusPlus, "++"));
					++i;
					// LogString("Extracted lexeme: +=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Plus, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '/':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::SlashEqual, "/="));
					++i;
					// LogString("Extracted lexeme: /=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::ForwardSlash, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '*':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::AsteriskEqual, "*="));
					++i;
					// LogString("Extracted lexeme: *=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Asterisk, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '%':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::PercentEqual, "%="));
					++i;
					// LogString("Extracted lexeme: %=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Percent, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '&':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::AmpersandEqual, "&="));
					++i;
					// LogString("Extracted lexeme: &=");
				}
				else if (MatchNext('|', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::DoubleAmpersand, "&&"));
					++i;
					// LogString("Extracted lexeme: &&");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::VerticalBar, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '|':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::VerticalBarEqual, "|="));
					++i;
					// LogString("Extracted lexeme: |=");
				}
				else if (MatchNext('|', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::DoubleVerticalBar, "||"));
					++i;
					// LogString("Extracted lexeme: ||");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::VerticalBar, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '^':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::CaretEqual, "^="));
					++i;
					// LogString("Extracted lexeme: ^=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Caret, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '!':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::BangEqual, "!="));
					++i;
					// LogString("Extracted lexeme: !=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Bang, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '~':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::TildeEqual, "~="));
					++i;
					// LogString("Extracted lexeme: ~=");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Tilde, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '=':
				if (MatchNext('=', i + 1))
				{
					tokens.push_back(CreateToken(TokenType::EqualEqual, "="));
					++i;
					// LogString("Extracted lexeme: ==");
				}
				else
				{
					tokens.push_back(CreateToken(TokenType::Equal, ConvertToString(current_char)));
					// LogString(std::string("Extracted lexeme: ") + current_char);
				}
				break;
			case '"':
				if (current_token.token_type == TokenType::StringLiteral)
				{
					// if the current lexeme is a string literal then a quote will finish it
					// note that a preceding backslash will escape a string literal
					if (i > 0 && prog_string[i - 1] == '\\')
					{
						// escape char here
						current_token.lexeme += current_char;
					}
					else
					{
						tokens.push_back(current_token);
						// LogString("Extracted lexeme: " + current_token.lexeme);
						current_token = CreateToken(TokenType::Unknown, "");
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
				else if (current_token.token_type == TokenType::NumericLiteral && current_char == 'f')
				{
					current_token.lexeme += current_char;
					current_token = AddToken(tokens, current_token);
				}
				else if (current_token.token_type == TokenType::Identifier && IsIdentifier(current_char))
				{
					current_token.lexeme += current_char;
				}
				else if (current_token.token_type == TokenType::Unknown && IsIdentifierStart(current_char))
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
		return true;

	}

	bool Scanner::ScanFile(const std::string & path, std::vector<Token> & tokens)
	{
		std::string file_contents = ReadWholeFile(path);
		std::cout << file_contents << "\n";

		return ScanString(file_contents, tokens);

	}
	Token Scanner::CreateToken(TokenType type, const std::string& lexeme)
	{
		Token token(type, lexeme);
		token.line = line_;
		token.col = col_;

		return token;
	}
}