#pragma once

/// Utility Functions
/// TODO: Add UTF-8 support

// std::isalpha, std::isdigit
#include <cctype>
#include <string>

namespace SDIM
{
	bool IsWhitespace(char c);
	/// Is the character a valid identifier start character
	/// This is true if the character is either '_' or a char in the ranges 'A' .. 'Z' or 'a' .. 'z'
	bool IsIdentifierStart(char c);
	
	/// Is the character a valid character for the 2nd position onwards in an identifier
	/// To be a valid char it must either pass the above is identifier start function or be in the range '0' .. '9'
	bool IsIdentifier(char c);
	
	/// Reads a text file and preserves all characters contained within (does not exclude whitespace)
	std::string ReadWholeFile(const std::string& path);
}