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

	union VarUnion
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
		VarUnion() { ptr = nullptr; }
	};

	
	struct Variable
	{
		VariableType type;

		VarUnion as;

		Variable() : type(SDIM::VariableType::Unknown), as(SDIM::VarUnion()) {}

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

		bool IsSameType(const Variable& other);
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

	constexpr size_t opcode_size = 1;
	/// TODO: Find a better place for this to be shared between the Compiler and VM
	enum class Instruction : UInt8
	{
		NOP = 0x00,
		VMCall = 0x01,
		Call = 0x02,
		Jmp = 0x03,
		JmpStack = 0x04,
		JmpTStack = 0x05,
		JmpFStack = 0x06,
		Return = 0x07,
		JmpT = 0x08,
		JmpF = 0x09,
		CallT = 0x0A,
		CallF = 0x0B,
		CallTStack = 0x0C,
		CallFStack = 0x0D,
		NativeCall = 0x0E,
		Less = 0x0F,
		LessEqual = 0x10,
		Greater = 0x11,
		GreaterEqual = 0x12,
		Equal = 0x13,
		NotEqual = 0x14,
		Not = 0x15,
		And = 0x16, // Bitwise AND not logical AND
		Or = 0x17,  // Bitwise OR not logical OR
		Xor = 0x18, // Bitwise XOR not logical XOR
		Add = 0x19,
		Subtract = 0x1A,
		Multiply = 0x1B,
		BitwiseNot = 0x1C,
		Divide = 0x1D,
		Negate = 0x1E,
		Modulo = 0x1F,
		PushInt8 = 0x20,
		PushInt16 = 0x21,
		PushInt32 = 0x22,
		PushInt64 = 0x23,
		PushUInt8 = 0x24,
		PushUInt16 = 0x25,
		PushUInt32 = 0x26,
		PushUInt64 = 0x27,
		PushF32 = 0x28,
		PushF64 = 0x29,
		PushPointer = 0x2A,
		PushString = 0x2B,
		PushStruct = 0x2C,
		PushClass = 0x2D,
		LocalVar = 0x2E,
		Pop = 0x2F,
		PushLocal = 0x30,

		PushAddr = 0x41,
		Break = 0x42,
		PushStackCount = 0x43,
		Dump = 0x44,
		Error = 0x45,
		Halt = 0x48,
		Pause = 0x50,
		PushInfoString = 0x53

	};
	// number of allowed single byte opcodes
	constexpr size_t MAX_OPCODES = 256;
}