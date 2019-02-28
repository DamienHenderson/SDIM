#pragma once

#include <cstdint>
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
		Pointer
	};
	struct Variable
	{
		VariableType type;

		union
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

		} as;
	};
	
}