#pragma once

enum class TokenType
{
	// Reserved Words
	If, Else, ElseIf, While, Do, True, False,
	Break, Return, Module, Include,

	// Mathematical Operators
	Add, Subtract, Divide, Multiply, Modulo, Brackets, LeftShift, RightShift, UnaryNegate,


	// Logical Operators
	Equivalent, NotEquivalent, GreaterThan, GreaterEqual, LessThan, LessEqual, LogicalNot,
	BitwiseAnd, LogicalAnd, BitwiseOr, LogicalOr, BitwiseXor, LogicalXor, BitwiseNot,

	// Miscellaneous
	EOF, OpenScope, CloseScope
};
// TODO: Operator Precedence
// Base operator precedence off of C++ to surprise users the least

class Token
{
public:
	Token();
	virtual ~Token();

	virtual TokenType GetType() const
	{

	}
};

