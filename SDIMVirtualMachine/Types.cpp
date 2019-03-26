#include "Types.hpp"

#include <sstream>

#include "Utils.hpp"
namespace SDIM
{
	std::string Variable::ToString()
	{
		switch (type)
		{
		case SDIM::VariableType::UInt8:
			return SDIM::Utils::ConstructString("UInt8: ", as.uint8);

		case SDIM::VariableType::UInt16:
			return SDIM::Utils::ConstructString("UInt16: ", as.uint16);

		case SDIM::VariableType::UInt32:
			return SDIM::Utils::ConstructString("UInt32: ", as.uint32);

		case SDIM::VariableType::UInt64:
			return SDIM::Utils::ConstructString("UInt64: ", as.uint64);

		case SDIM::VariableType::Int8:
			return SDIM::Utils::ConstructString("Int8: ", as.int8);

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
}