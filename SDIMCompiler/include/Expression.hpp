#pragma once

#include "Types.hpp"

namespace SDIM
{
	enum class ExpressionType
	{
		Prefix,
		Postfix,
		Infix,
		Conditional,

	};

	class Expression
	{
	public:
		Expression() {}
		virtual ~Expression() {}

		virtual UInt64 GetPrecedence() const = 0;

		virtual UInt64 GetExpressionType() const = 0;
	};
}