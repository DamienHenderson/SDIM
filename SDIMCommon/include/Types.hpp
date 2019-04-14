#pragma once

#include <cstdint>
#include <string>

namespace SDIM
{
	typedef std::uint8_t  UInt8;
	typedef std::uint16_t UInt16;
	typedef std::uint32_t UInt32;
	typedef std::uint64_t UInt64;

	typedef std::int8_t  Int8;
	typedef std::int16_t Int16;
	typedef std::int32_t Int32;
	typedef std::int64_t Int64;

	typedef float F32;
	typedef double F64;

	enum class VariableType : UInt8
	{
	 
		UInt8,
		UInt16,
		UInt32,
		UInt64,

		Int8,
		Int16,
		Int32,
		Int64,

		F32,
		F64,
		Pointer,
		Unknown
	};

	typedef union
	{
		Int8  int8;
		Int16 int16;
		Int32 int32;
		Int64 int64;


		UInt8  uint8;
		UInt16 uint16;
		UInt32 uint32;
		UInt64 uint64;

		F32 f32;
		F64 f64;

		void* ptr;

	} VarUnion;
	struct Variable
	{
		VariableType type;

		VarUnion as;

		Variable() : type(SDIM::VariableType::Unknown) {}

		Variable(VariableType var_type, VarUnion value) : type(var_type), as(value) {}

		Variable(UInt8 val);
		Variable(UInt16 val);
		Variable(UInt32 val);
		Variable(UInt64 val);

		Variable(Int8 val);
		Variable(Int16 val);
		Variable(Int32 val);
		Variable(Int64 val);

		Variable(F32 val);
		Variable(F64 val);
		
		Variable(void* val);

		std::string ToString();
	};

	bool IsTrue(const SDIM::Variable& var);
	bool IsFalse(const SDIM::Variable& var);
	namespace Utils
	{
		F32 UInt32ToF32(UInt32 val);
		F64 UInt64ToF64(UInt64 val);
		void* UInt64ToPtr(UInt64 val);
	}

	constexpr UInt8 True = 1;
	constexpr UInt8 False = 0;
}