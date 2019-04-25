#include "Types.hpp"

#include <sstream>

#include "Utils.hpp"
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
	std::string Variable::ToString()
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
	bool Variable::IsSameType(const Variable& other)
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
		void * UInt64ToPtr(UInt64 val)
		{
			static_assert(sizeof(UInt64) == sizeof(void*), "Size mismatch between UInt64 and Pointer type");
			return reinterpret_cast<void*>(val);
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
	Variable::Variable(void * val)
	{
		type = VariableType::Pointer;
		as.ptr = val;
	}
}