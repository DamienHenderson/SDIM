#pragma once

#include "Types.hpp"
#include "Token.hpp"

#include <array>
namespace SDIM
{
	
	enum class Precedence
	{
		// C++11 operator precedence rules
		 None = 0,
		 // ,
		 Comma = 1,
		 // = and compound assignment
		 Assignment = 2,
		 // ||
		 LogicalOr = 3,
		 // &&
		 LogicalAnd = 4,
		 // |
		 BitwiseOr = 5,
		 // ^
		 BitwiseXor = 6,
		 // &
		 BitwiseAnd = 7,
		 // ==
		 Equivalence = 8,
		 // <, <=, >, >=
		 Relational = 9,
		 // <<, >>
		 Shift = 10,
		 // +, -
		 Addition = 11,
		 // *, /, %
		 Product = 12,
		 // -x
		 Unary = 13,
		 // --x, ++x
		 Prefix = 13,
		 // --x, x++
		 Postfix = 14,
		 // x()
		 Call = 15,
	

	
	};
	
	Precedence GetPrecedence(TokenType token_type);

	
	
}