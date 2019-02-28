#pragma once

#include <string>

namespace SDIM
{


	enum class TokenType
	{
		// Keywords
		If, Else, ElseIf, While, Do, True, False,
		Break, Return, Module, Include,

		// Mathematical Operators
		Add, Subtract, Divide, Multiply, Modulo, Brackets, LeftShift, RightShift, UnaryNegate,


		// Logical Operators
		Equivalent, NotEquivalent, GreaterThan, GreaterEqual, LessThan, LessEqual, LogicalNot,
		BitwiseAnd, LogicalAnd, BitwiseOr, LogicalOr, BitwiseXor, LogicalXor, BitwiseNot,

		// Miscellaneous
		EOFToken, OpenScope, CloseScope
	};
	// TODO: Operator Precedence
	// Base operator precedence off of C++ to surprise users the least

	struct Token
	{
		TokenType token_type;

		std::string lexeme;
	};

}