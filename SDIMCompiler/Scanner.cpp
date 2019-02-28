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

	bool Scanner::ScanFile(const std::string & path,std::vector<Token>& tokens)
	{
		std::string file_contents = ReadWholeFile(path);
		std::cout << file_contents;
		Token current;
		for (size_t i = 0; i < file_contents.size(); i++)
		{
			char current_char = file_contents[i];

			if (!IsWhitespace(current_char))
			{
				current.lexeme += current_char;
			}
			else
			{
				tokens.push_back(current);
				std::cout << "Extracted lexeme: " << current.lexeme << "\n";
				current = Token();
			}
		}

		return false;
	}

}