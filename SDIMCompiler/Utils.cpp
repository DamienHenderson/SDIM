#include "Utils.hpp"

#include <fstream>
#include <iostream>

namespace SDIM
{
	bool IsWhitespace(char c)
	{
		return c == ' ' || c == '\n' || c == '\r' || c == '\t';
	}
	bool IsIdentifierStart(char c)
	{
		if (std::isalpha(c))
		{
			return true;
		}
		else if (c == '_')
		{
			return true;
		}

		return false;
	}
	bool IsIdentifier(char c)
	{
		if (IsIdentifierStart(c))
		{
			return true;
		}
		// check if the char is a digit in the range '0' .. '9'
		else if (std::isdigit(c))
		{
			return true;
		}
		return false;
	}
	std::string ReadWholeFile(const std::string & path)
	{
		std::ifstream ifs(path);
		return std::string((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
	}

	void LogString(const std::string & message)
	{
#ifdef SDIMC_DEBUG
		std::cerr << message << "\n";
#endif
	}

	std::string ConvertToString(char c)
	{
		return std::string() + c;
	};


}