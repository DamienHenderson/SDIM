#pragma once

/// Utility Functions
/// TODO: Add UTF-8 support

// std::isalpha, std::isdigit
#include <cctype>

bool IsWhitespace(char c)
{
	return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}
/// Is the character a valid identifier start character
/// This is true if the character is either '_' or a char in the ranges 'A' .. 'Z' or 'a' .. 'z'
inline bool IsIdentifierStart(char c)
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
/// Is the character a valid character for the 2nd position onwards in an identifier
/// To be a valid char it must either pass the above is identifier start function or be in the range '0' .. '9'
inline bool IsIdentifier(char c)
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

bool IsOpenScope(char c)
{
	return c == '{';
}
bool IsCloseScope(char c)
{
	return c == '}';
}