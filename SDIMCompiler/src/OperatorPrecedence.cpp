#include "OperatorPrecedence.hpp"

namespace SDIM
{
	Precedence GetPrecedence(TokenType token_type)
	{
		switch (token_type)
		{
			// comma 
		case TokenType::Comma:
			return Precedence::Comma;
			// assignment
		case TokenType::Equal:
			return Precedence::Assignment;
		case TokenType::VerticalBarEqual:
			return Precedence::Assignment;
		case TokenType::AmpersandEqual:
			return Precedence::Assignment;
		case TokenType::CaretEqual:
			return Precedence::Assignment;
		case TokenType::PlusEqual:
			return Precedence::Assignment;
		case TokenType::MinusEqual:
			return Precedence::Assignment;
		case TokenType::SlashEqual:
			return Precedence::Assignment;
		case TokenType::AsteriskEqual:
			return Precedence::Assignment;
		case TokenType::PercentEqual:
			return Precedence::Assignment;
		case TokenType::TildeEqual:
			return Precedence::Assignment;
			// logical or
		case TokenType::DoubleVerticalBar:
			return Precedence::LogicalOr;
			// logical and
		case TokenType::DoubleAmpersand:
			return Precedence::LogicalAnd;
			// bitwise or
		case TokenType::VerticalBar:
			return Precedence::BitwiseOr;
			// bitwise xor
		case TokenType::Caret:
			return Precedence::BitwiseXor;
			// bitwise and
		case TokenType::Ampersand:
			return Precedence::BitwiseAnd;
			// equivalent
		case TokenType::EqualEqual:
			return Precedence::Equivalence;
			// not equivalent
		case TokenType::BangEqual:
			return Precedence::Equivalence;
			// less than
		case TokenType::LessThan:
			return Precedence::Relational;
			// less equal
		case TokenType::LessEqual:
			return Precedence::Relational;
			// greater than
		case TokenType::GreaterThan:
			return Precedence::Relational;
			// greater equal
		case TokenType::GreaterEqual:
			return Precedence::Relational;
			// left shift
		case TokenType::LeftShift:
			return Precedence::Shift;
			// right shift
		case TokenType::RightShift:
			return Precedence::Shift;
			// add
		case TokenType::Plus:
			return Precedence::Addition;
			// subtract
		case TokenType::Minus:
			return Precedence::Addition;
			// multiply
		case TokenType::Asterisk:
			return Precedence::Product;
			// divide
		case TokenType::ForwardSlash:
			return Precedence::Product;
			// modulo
		case TokenType::Percent:
			return Precedence::Product;
			// subtract
		case TokenType::PlusPlus:
			return Precedence::Unary;
		case TokenType::MinusMinus:
			return Precedence::Unary;
		case TokenType::Bang:
			return Precedence::Unary;
		case TokenType::Tilde:
			return Precedence::Unary;
		case TokenType::LeftBracket:
			return Precedence::Call;
		default:
			return Precedence::None;
		}

	}
}