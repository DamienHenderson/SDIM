#include "BytecodeGenerator.hpp"

#include <Types.hpp>
#include <Utils.hpp>
namespace SDIM
{
	void BytecodeGenerator::WriteJumpInstruction(std::vector<unsigned char>& prog_data, UInt64 addr)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Jmp);
		prog_data.push_back(inst);

		UInt64 addr_little_endian = Utils::UInt64ToLittleEndian(addr);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* addr_bytes = (unsigned char*)&addr_little_endian;
		for (size_t i = 0; i < sizeof(addr_little_endian); ++i)
		{
			prog_data.push_back(addr_bytes[i]);
		}

	}
	void BytecodeGenerator::WriteCallInstruction(std::vector<unsigned char>& prog_data, UInt64 addr)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Call);
		prog_data.push_back(inst);

		UInt64 addr_little_endian = Utils::UInt64ToLittleEndian(addr);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* addr_bytes = (unsigned char*)& addr_little_endian;
		for (size_t i = 0; i < sizeof(addr_little_endian); ++i)
		{
			prog_data.push_back(addr_bytes[i]);
		}

	}
	void BytecodeGenerator::WritePushUInt8Instruction(std::vector<unsigned char>& prog_data, UInt8 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushUInt8);
		prog_data.push_back(inst);
		prog_data.push_back(value);
	}
	void BytecodeGenerator::WritePushUInt16Instruction(std::vector<unsigned char>& prog_data, UInt16 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushUInt16);
		prog_data.push_back(inst);
		UInt16 value_little_endian = Utils::UInt16ToLittleEndian(value);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* value_bytes = (unsigned char*)& value_little_endian;
		for (size_t i = 0; i < sizeof(value_little_endian); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WritePushUInt32Instruction(std::vector<unsigned char>& prog_data, UInt32 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushUInt32);
		prog_data.push_back(inst);
		UInt32 value_little_endian = Utils::UInt32ToLittleEndian(value);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* value_bytes = (unsigned char*)& value_little_endian;
		for (size_t i = 0; i < sizeof(value_little_endian); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WritePushUInt64Instruction(std::vector<unsigned char>& prog_data, UInt64 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushUInt64);
		prog_data.push_back(inst);
		UInt64 value_little_endian = Utils::UInt64ToLittleEndian(value);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* value_bytes = (unsigned char*)& value_little_endian;
		for (size_t i = 0; i < sizeof(value_little_endian); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WritePushInt8Instruction(std::vector<unsigned char>& prog_data, Int8 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushInt8);
		prog_data.push_back(inst);
		prog_data.push_back((unsigned char)value);
	}
	void BytecodeGenerator::WritePushInt16Instruction(std::vector<unsigned char>& prog_data, Int16 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushInt16);
		prog_data.push_back(inst);
		UInt16 value_little_endian = Utils::UInt16ToLittleEndian(Utils::ByteCast<UInt16>(value));
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* value_bytes = (unsigned char*)& value_little_endian;
		for (size_t i = 0; i < sizeof(value_little_endian); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}

	}
	void BytecodeGenerator::WritePushInt32Instruction(std::vector<unsigned char>& prog_data, Int32 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushInt32);
		prog_data.push_back(inst);
		UInt32 value_little_endian = Utils::UInt32ToLittleEndian(Utils::ByteCast<UInt32>(value));
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* value_bytes = (unsigned char*)& value_little_endian;
		for (size_t i = 0; i < sizeof(value_little_endian); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WritePushInt64Instruction(std::vector<unsigned char>& prog_data, Int64 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushInt64);
		prog_data.push_back(inst);
		UInt64 value_little_endian = Utils::UInt64ToLittleEndian(Utils::ByteCast<UInt64>(value));
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* value_bytes = (unsigned char*)& value_little_endian;
		for (size_t i = 0; i < sizeof(value_little_endian); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WritePushF32Instruction(std::vector<unsigned char>& prog_data, F32 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushF32);
		prog_data.push_back(inst);
		// Assume no endianness for floating point
		// TODO: serialise in IEEE754 format
		unsigned char* value_bytes = (unsigned char*)& value;
		for (size_t i = 0; i < sizeof(value); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WritePushF64Instruction(std::vector<unsigned char>& prog_data, F64 value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushF64);
		prog_data.push_back(inst);
		// Assume no endianness for floating point
		// TODO: serialise in IEEE754 format
		unsigned char* value_bytes = (unsigned char*)& value;
		for (size_t i = 0; i < sizeof(value); ++i)
		{
			prog_data.push_back(value_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteHaltInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Halt);
		prog_data.push_back(inst);
	}
}