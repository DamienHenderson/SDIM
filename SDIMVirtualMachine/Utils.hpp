#pragma once

#include "Types.hpp"

#include <string>

namespace SDIM
{
	namespace Utils
	{
		// This shouldn't be constexpr because the entire point is querying at runtime 
		// If it was constexpr the querying would be at compile time and would be totally useless because 
		// it would refer to the endianness of the machine compiling it
		bool IsLittleEndian();

		void LogString(const std::string& log_str);
	}
}