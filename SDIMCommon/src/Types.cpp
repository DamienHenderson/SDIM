#include "Types.hpp"

#include <sstream>

#include "Utils.hpp"

#include <cmath>
namespace SDIM
{
	constexpr size_t type_sizes[] = {
		// unsigned types
		sizeof(UInt8),
		sizeof(UInt16),
		sizeof(UInt32),
		sizeof(UInt64),
		// signed types
		sizeof(Int8),
		sizeof(Int16),
		sizeof(Int32),
		sizeof(Int64),
		// floating point types
		sizeof(F32),
		sizeof(F64),
		// Pointer types
		sizeof(void*),
		sizeof(char*),
		// unknown
		0

	};
	std::string Variable::ToString() const
	{
		switch (type)
		{
		case SDIM::VariableType::UInt8:
			return SDIM::Utils::ConstructString("UInt8: ", +as.uint8);

		case SDIM::VariableType::UInt16:
			return SDIM::Utils::ConstructString("UInt16: ", as.uint16);

		case SDIM::VariableType::UInt32:
			return SDIM::Utils::ConstructString("UInt32: ", as.uint32);

		case SDIM::VariableType::UInt64:
			return SDIM::Utils::ConstructString("UInt64: ", as.uint64);

		case SDIM::VariableType::Int8:
			return SDIM::Utils::ConstructString("Int8: ", +as.int8);

		case SDIM::VariableType::Int16:
			return SDIM::Utils::ConstructString("Int16: ", as.int16);

		case SDIM::VariableType::Int32:
			return SDIM::Utils::ConstructString("Int32: ", as.int32);

		case SDIM::VariableType::Int64:
			return SDIM::Utils::ConstructString("Int64: ", as.int64);

		case SDIM::VariableType::F32:
			return SDIM::Utils::ConstructString("F32: ", as.f32);

		case SDIM::VariableType::F64:
			return SDIM::Utils::ConstructString("F64: ", as.f64);

		case SDIM::VariableType::Pointer:
			return SDIM::Utils::ConstructString("Pointer: ", as.ptr);

		case SDIM::VariableType::Unknown:
			return SDIM::Utils::ConstructString("ERROR! Unknown Type");
		default:
			return SDIM::Utils::ConstructString("ERROR! Unknown Type");
		}
	}
	size_t Variable::GetTypeSize() const
	{
		return type_sizes[static_cast<size_t>(type)];
	}
	bool Variable::IsSameType(const Variable & other) const
	{
		return type == other.type;
	}
	bool Variable::IsInteger() const
	{
		return type == VariableType::Int8 || type == VariableType::Int16 || type == VariableType::Int32 || type == VariableType::Int64;
	}
	bool Variable::IsUnsigned() const
	{
		return type == VariableType::UInt8 || type == VariableType::UInt16 || type == VariableType::UInt32 || type == VariableType::UInt64;
	}
	bool Variable::IsFloat() const
	{
		return type == VariableType::F32 || type == VariableType::F64;
	}

	bool Variable::IsNumeric() const
	{
		return IsInteger() || IsUnsigned() || IsFloat();
	}



	bool Variable::ShouldPromoteToOtherType(const Variable & other) const
	{
		if (IsInteger() && other.IsInteger() && other.GetTypeSize() >= GetTypeSize())
		{
			return true;
		}
		if (IsUnsigned() && other.IsUnsigned() && other.GetTypeSize() >= GetTypeSize())
		{
			return true;
		}
		if (IsFloat() && other.IsFloat() && other.GetTypeSize() >= GetTypeSize())
		{
			return true;
		}

		return false;
	}



	Variable Variable::PromoteToOtherType(const Variable & other) const
	{
		if (IsInteger() && other.IsInteger() && other.GetTypeSize() <= GetTypeSize())
		{
			return *this;
		}
		if (IsUnsigned() && other.IsUnsigned() && other.GetTypeSize() <= GetTypeSize())
		{
			return *this;
		}
		if (IsFloat() && other.IsFloat() && other.GetTypeSize() <= GetTypeSize())
		{
			return *this;
		}

		return Variable();

	}

	namespace Operators
	{

		// Logical Operators
		namespace detail
		{
			bool LessInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 < rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 < rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 < rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 < rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 < rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 < rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 < rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 < rhs.as.int64;
					// floating point
				case VariableType::F32:
					return lhs.as.f32 < rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 < rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					return lhs.as.ptr < rhs.as.ptr;
					// case VariableType::String:
					//	return lhs.as.f64 < rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}

			bool GreaterInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 > rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 > rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 > rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 > rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 > rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 > rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 > rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 > rhs.as.int64;
					// floating point
				case VariableType::F32:
					return lhs.as.f32 > rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 > rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					return lhs.as.ptr > rhs.as.ptr;
					// case VariableType::String:
					//	return lhs.as.f64 > rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}

			bool EqualInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 == rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 == rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 == rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 == rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 == rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 == rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 == rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 == rhs.as.int64;
					// floating point
				case VariableType::F32:
					return lhs.as.f32 == rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 == rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					return lhs.as.ptr == rhs.as.ptr;
					// case VariableType::String:
					//	return lhs.as.f64 == rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}
			bool NotEqualInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 != rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 != rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 != rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 != rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 != rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 != rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 != rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 != rhs.as.int64;
					// floating point
				case VariableType::F32:
					return lhs.as.f32 != rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 != rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					return lhs.as.ptr != rhs.as.ptr;
					// case VariableType::String:
					//	return lhs.as.f64 != rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}
			Variable NotInternal(const Variable& var)
			{
				switch (var.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return !var.as.uint8;
				case VariableType::UInt16:
					return !var.as.uint16;
				case VariableType::UInt32:
					return !var.as.uint32;
				case VariableType::UInt64:
					return !var.as.uint64;
					// signed
				case VariableType::Int8:
					return !var.as.int8;
				case VariableType::Int16:
					return !var.as.int16;
				case VariableType::Int32:
					return !var.as.int32;
				case VariableType::Int64:
					return !var.as.int64;
					// floating point
				case VariableType::F32:
					return !var.as.f32;
				case VariableType::F64:
					return !var.as.f64;
					// pointers
				case VariableType::Pointer:
					return !var.as.ptr;
					// case VariableType::String:
					//	return var.as.f64 != rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}
			Variable AndInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8& rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16& rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32& rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64& rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8& rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16& rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32& rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64& rhs.as.int64;
					// floating point
					// below this point this operation is not applicable
					// Runtime Errors below this point
				case VariableType::F32:
					return Variable();
				case VariableType::F64:
					return Variable();
					// pointers
				case VariableType::Pointer:
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable OrInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 | rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 | rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 | rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 | rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 | rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 | rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 | rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 | rhs.as.int64;
					// floating point
					// below this point this operation is not applicable
					// Runtime Errors below this point
				case VariableType::F32:
					return Variable();
				case VariableType::F64:
					return Variable();
					// pointers
				case VariableType::Pointer:
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable XorInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8^ rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16^ rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32^ rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64^ rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8^ rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16^ rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32^ rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64^ rhs.as.int64;
					// floating point
					// below this point this operation is not applicable
					// Runtime Errors below this point
				case VariableType::F32:
					return Variable();
				case VariableType::F64:
					return Variable();
					// pointers
				case VariableType::Pointer:
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable AddInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 + rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 + rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 + rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 + rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 + rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 + rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 + rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 + rhs.as.int64;
					// floating point

				case VariableType::F32:
					return lhs.as.f32 + rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 + rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					// pointer
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable SubtractInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 - rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 - rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 - rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 - rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 - rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 - rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 - rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 - rhs.as.int64;
					// floating point

				case VariableType::F32:
					return lhs.as.f32 - rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 - rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					// pointer
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable MultiplyInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8* rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16* rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32* rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64* rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8* rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16* rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32* rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64* rhs.as.int64;
					// floating point

				case VariableType::F32:
					return lhs.as.f32* rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64* rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					// pointer
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable BitwiseNotInternal(const Variable& var)
			{
				switch (var.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return ~var.as.uint8;
				case VariableType::UInt16:
					return ~var.as.uint16;
				case VariableType::UInt32:
					return ~var.as.uint32;
				case VariableType::UInt64:
					return ~var.as.uint64;
					// signed
				case VariableType::Int8:
					return ~var.as.int8;
				case VariableType::Int16:
					return ~var.as.int16;
				case VariableType::Int32:
					return ~var.as.int32;
				case VariableType::Int64:
					return ~var.as.int64;
					// floating point
				case VariableType::F32:
					return Variable();
				case VariableType::F64:
					return Variable();
					// pointers
				case VariableType::Pointer:
					return Variable();
					// case VariableType::String:
					//	return var.as.f64 ~= rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}
			Variable DivideInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8 / rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16 / rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32 / rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64 / rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8 / rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16 / rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32 / rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64 / rhs.as.int64;
					// floating point

				case VariableType::F32:
					return lhs.as.f32 / rhs.as.f32;
				case VariableType::F64:
					return lhs.as.f64 / rhs.as.f64;
					// pointers
				case VariableType::Pointer:
					// pointer
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
			Variable NegateInternal(const Variable& var)
			{
				switch (var.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return Variable();
				case VariableType::UInt16:
					return Variable();
				case VariableType::UInt32:
					return Variable();
				case VariableType::UInt64:
					return Variable();
					// signed
				case VariableType::Int8:
					return -var.as.int8;
				case VariableType::Int16:
					return -var.as.int16;
				case VariableType::Int32:
					return -var.as.int32;
				case VariableType::Int64:
					return -var.as.int64;
					// floating point
				case VariableType::F32:
					return -var.as.f32;
				case VariableType::F64:
					return -var.as.f64;
					// pointers
				case VariableType::Pointer:
					return Variable();
					// case VariableType::String:
					//	return var.as.f64 -= rhs.as.f64;
				default:
					// unknown type
					return false;
				}
			}
			Variable ModuloInternal(const Variable& lhs, const Variable& rhs)
			{
				switch (lhs.type)
				{
					// unsigned 
				case VariableType::UInt8:
					return lhs.as.uint8% rhs.as.uint8;
				case VariableType::UInt16:
					return lhs.as.uint16% rhs.as.uint16;
				case VariableType::UInt32:
					return lhs.as.uint32% rhs.as.uint32;
				case VariableType::UInt64:
					return lhs.as.uint64% rhs.as.uint64;
					// signed
				case VariableType::Int8:
					return lhs.as.int8% rhs.as.int8;
				case VariableType::Int16:
					return lhs.as.int16% rhs.as.int16;
				case VariableType::Int32:
					return lhs.as.int32% rhs.as.int32;
				case VariableType::Int64:
					return lhs.as.int64% rhs.as.int64;
					// floating point

				case VariableType::F32:
					return fmodf(lhs.as.f32, rhs.as.f32);
				case VariableType::F64:
					return fmod(lhs.as.f64, rhs.as.f64);
					// pointers
				case VariableType::Pointer:
					// pointer
					return Variable();
				default:
					// unknown type
					return Variable();
				}
			}
		}
		bool Less(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::LessInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::LessInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::LessInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return false;
				}
			}
		}
		bool LessEqual(const Variable& lhs, const Variable& rhs)
		{
			return Less(lhs, rhs) || Equal(lhs, rhs);
		}
		bool Greater(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::GreaterInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::GreaterInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::GreaterInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return false;
				}
			}
		}
		bool GreaterEqual(const Variable& lhs, const Variable& rhs)
		{
			return Greater(lhs, rhs) || Equal(lhs, rhs);
		}
		bool Equal(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::EqualInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::EqualInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::EqualInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return false;
				}
			}
		}
		bool NotEqual(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::NotEqualInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::NotEqualInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::NotEqualInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return false;
				}
			}
		}
		Variable Not(const Variable& var)
		{
			return detail::NotInternal(var);
		}

		// Arithmetic Operators
		Variable And(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::AndInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::AndInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::AndInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable Or(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::OrInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::OrInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::OrInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable Xor(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::XorInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::XorInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::XorInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable Add(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::AddInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::AddInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::AddInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable Subtract(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::SubtractInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::SubtractInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::SubtractInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable Multiply(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::MultiplyInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::MultiplyInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::MultiplyInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable BitwiseNot(const Variable& var)
		{
			return detail::BitwiseNotInternal(var);
		}
		Variable Divide(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::DivideInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::DivideInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::DivideInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
		Variable Negate(const Variable& var)
		{
			return detail::NegateInternal(var);
		}
		Variable Modulo(const Variable& lhs, const Variable& rhs)
		{
			if (lhs.IsSameType(rhs))
			{
				return detail::ModuloInternal(lhs, rhs);
			}
			else
			{
				if (lhs.ShouldPromoteToOtherType(rhs))
				{
					Variable lhs_promoted = lhs.PromoteToOtherType(rhs);
					return detail::ModuloInternal(lhs_promoted, rhs);
				}
				else if (rhs.ShouldPromoteToOtherType(lhs))
				{
					Variable rhs_promoted = rhs.PromoteToOtherType(lhs);
					return detail::ModuloInternal(lhs, rhs_promoted);
				}
				else
				{
					// type mismatch
					// TODO: Runtime Error here
					return Variable();
				}
			}
		}
	}

	bool IsTrue(const SDIM::Variable & var)
	{
		switch (var.type)
		{
		case VariableType::UInt8:
			return var.as.uint8 != 0;
		case VariableType::UInt16:
			return var.as.uint16 != 0;
		case VariableType::UInt32:
			return var.as.uint32 != 0;
		case VariableType::UInt64:
			return var.as.uint64 != 0;

		case VariableType::Int8:
			return var.as.int8 != 0;
		case VariableType::Int16:
			return var.as.int16 != 0;
		case VariableType::Int32:
			return var.as.int32 != 0;
		case VariableType::Int64:
			return var.as.int64 != 0;

		case VariableType::F32:
			return var.as.f32 != 0.0f;
		case VariableType::F64:
			return var.as.f64 != 0.0;

		case VariableType::Pointer:
			return var.as.ptr != nullptr;
		default:
			return false;
		}
	}
	bool IsFalse(const SDIM::Variable & var)
	{
		return !IsTrue(var);
	}
	namespace Utils
	{
		F32 UInt32ToF32(UInt32 val)
		{
			static_assert(sizeof(UInt32) == sizeof(F32), "Size mismatch between F32 and UInt32");
			// massive hack but it works well enough for now
			union
			{
				UInt32 ui;
				F32 f;
			} mem_cast;
			mem_cast.ui = val;
			return mem_cast.f;
		}
		F64 UInt64ToF64(UInt64 val)
		{
			static_assert(sizeof(UInt64) == sizeof(F64), "Size mismatch between F64 and UInt64");
			// massive hack but it works well enough for now 
			union
			{
				UInt64 ui;
				F64 f;
			} mem_cast;
			mem_cast.ui = val;
			return mem_cast.f;
		}
		void* UInt64ToPtr(UInt64 val)
		{
			static_assert(sizeof(UInt64) == sizeof(void*), "Size mismatch between UInt64 and Pointer type");
			return reinterpret_cast<void*>(val);
		}
		UInt8 VariableTypeToUInt8(VariableType var_type)
		{
			return static_cast<UInt8>(var_type);
		}
	}
	Variable::Variable(UInt8 val)
	{
		type = VariableType::UInt8;
		as.uint8 = val;
	}
	Variable::Variable(UInt16 val)
	{
		type = VariableType::UInt16;
		as.uint16 = val;
	}
	Variable::Variable(UInt32 val)
	{
		type = VariableType::UInt32;
		as.uint32 = val;
	}
	Variable::Variable(UInt64 val)
	{
		type = VariableType::UInt64;
		as.uint64 = val;
	}
	Variable::Variable(Int8 val)
	{
		type = VariableType::Int8;
		as.int8 = val;
	}
	Variable::Variable(Int16 val)
	{
		type = VariableType::Int16;
		as.int16 = val;
	}
	Variable::Variable(Int32 val)
	{
		type = VariableType::Int32;
		as.int32 = val;
	}
	Variable::Variable(Int64 val)
	{
		type = VariableType::Int64;
		as.int64 = val;
	}
	Variable::Variable(F32 val)
	{
		type = VariableType::F32;
		as.f32 = val;
	}
	Variable::Variable(F64 val)
	{
		type = VariableType::F64;
		as.f64 = val;
	}
	Variable::Variable(void* val)
	{
		type = VariableType::Pointer;
		as.ptr = val;
	}




}

