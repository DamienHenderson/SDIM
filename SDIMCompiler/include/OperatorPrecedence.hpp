#pragma once

#include "Types.hpp"
#include "Token.hpp"

#include <array>
namespace SDIM
{
	// TODO: Operator Precedence
	// Base operator precedence off of C++ to surprise users the least
	namespace Precedence
	{
		// C++11 operator precedence rules
		// Function calls
		constexpr UInt64 Call = 2;
		// x++, x--
		constexpr UInt64 Postfix = 2;
		// ++x, --x
		constexpr UInt64 Prefix = 3;
		constexpr UInt64 Unary = 3;
		// Multiply divide and modulo
		constexpr UInt64 Product = 5;
		// Add and Subtract
		constexpr UInt64 Addition = 6;
		// Left and Right Bit Shifting
		constexpr UInt64 Shift = 7;
		// Less, LessEqual, Greater and GreaterEqual
		constexpr UInt64 Relational = 9;
		// Equal and Not Equal
		constexpr UInt64 Equivalence = 10;
		// &
		constexpr UInt64 BitwiseAnd = 11;
		// ^
		constexpr UInt64 BitwiseXor = 12;
		// |
		constexpr UInt64 BitwiseOr = 13;
		// &&
		constexpr UInt64 LogicalAnd = 14;
		// ||
		constexpr UInt64 LogicalOr = 15;
		// = and compound variants
		constexpr UInt64 Assignment = 16;
		// ,
		constexpr UInt64 Comma = 17;
		
		constexpr UInt64 None = 18;
	}
	
	
	

	
	
}