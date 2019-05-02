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
	void BytecodeGenerator::WriteJumpTrueInstruction(std::vector<unsigned char>& prog_data, UInt64 addr)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::JmpT);
		prog_data.push_back(inst);

		UInt64 addr_little_endian = Utils::UInt64ToLittleEndian(addr);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* addr_bytes = (unsigned char*)& addr_little_endian;
		for (size_t i = 0; i < sizeof(addr_little_endian); ++i)
		{
			prog_data.push_back(addr_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteJumpFalseInstruction(std::vector<unsigned char>& prog_data, UInt64 addr)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::JmpF);
		prog_data.push_back(inst);

		UInt64 addr_little_endian = Utils::UInt64ToLittleEndian(addr);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* addr_bytes = (unsigned char*)& addr_little_endian;
		for (size_t i = 0; i < sizeof(addr_little_endian); ++i)
		{
			prog_data.push_back(addr_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteJumpTrueStackInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::JmpTStack);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteJumpFalseStackInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::JmpFStack);
		prog_data.push_back(inst);
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
	void BytecodeGenerator::WriteCallTrueInstruction(std::vector<unsigned char>& prog_data, UInt64 addr)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::CallT);
		prog_data.push_back(inst);

		UInt64 addr_little_endian = Utils::UInt64ToLittleEndian(addr);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* addr_bytes = (unsigned char*)& addr_little_endian;
		for (size_t i = 0; i < sizeof(addr_little_endian); ++i)
		{
			prog_data.push_back(addr_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteCallFalseInstruction(std::vector<unsigned char>& prog_data, UInt64 addr)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::CallF);
		prog_data.push_back(inst);

		UInt64 addr_little_endian = Utils::UInt64ToLittleEndian(addr);
		// This cast is not very good i should see if i can do it in a better way
		unsigned char* addr_bytes = (unsigned char*)& addr_little_endian;
		for (size_t i = 0; i < sizeof(addr_little_endian); ++i)
		{
			prog_data.push_back(addr_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteCallTrueStackInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::CallTStack);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteCallFalseStackInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::CallFStack);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteReturnInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Return);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteLessInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Less);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteLessEqualInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::LessEqual);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteGreaterInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Greater);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteGreaterEqualInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::GreaterEqual);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteEqualInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Equal);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteNotEqualInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::NotEqual);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteNotInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Not);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteAndInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::And);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteOrInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Or);
		prog_data.push_back(inst);

	}
	void BytecodeGenerator::WriteXorInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Xor);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteBitwiseNotInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::BitwiseNot);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteAddInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Add);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteSubtractInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Subtract);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteMultiplyInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Multiply);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteDivideInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Divide);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteNegateInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Negate);
		prog_data.push_back(inst);
	}
	void BytecodeGenerator::WriteModuloInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Modulo);
		prog_data.push_back(inst);
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
	void BytecodeGenerator::WritePushStringInstruction(std::vector<unsigned char>& prog_data, const char* value)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushString);
		prog_data.push_back(inst);

		UInt64 len = std::strlen(value) + 1;
		unsigned char* len_bytes = (unsigned char*)& len;
		for (size_t i = 0; i < sizeof(len); ++i)
		{
			prog_data.push_back(len_bytes[i]);
		}

		for (UInt64 i = 0; i < len; i++)
		{
			prog_data.push_back(Utils::ByteCast<unsigned char>(value[i]));
		}

	}
	void BytecodeGenerator::WritePushLocalInstruction(std::vector<unsigned char>& prog_data, UInt64 idx)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::PushLocal);
		prog_data.push_back(inst);

		
		unsigned char* idx_bytes = (unsigned char*)& idx;
		for (size_t i = 0; i < sizeof(idx); ++i)
		{
			prog_data.push_back(idx_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteLocalVarInstruction(std::vector<unsigned char>& prog_data, UInt64 idx)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::LocalVar);
		prog_data.push_back(inst);


		unsigned char* idx_bytes = (unsigned char*)& idx;
		for (size_t i = 0; i < sizeof(idx); ++i)
		{
			prog_data.push_back(idx_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteVMCallInstruction(std::vector<unsigned char>& prog_data, UInt64 idx)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::VMCall);
		prog_data.push_back(inst);


		unsigned char* idx_bytes = (unsigned char*)& idx;
		for (size_t i = 0; i < sizeof(idx); ++i)
		{
			prog_data.push_back(idx_bytes[i]);
		}
	}
	void BytecodeGenerator::WriteHaltInstruction(std::vector<unsigned char>& prog_data)
	{
		UInt8 inst = Utils::InstructionToUInt8(Instruction::Halt);
		prog_data.push_back(inst);
	}
	GeneratorType BytecodeGenerator::GetType() const
	{
		return GeneratorType::BytecodeGenerator;
	}
	BytecodeHeader& BytecodeGenerator::GetHeader()
	{
		return header_;
	}
	void WriteBytecodeHeader(BytecodeHeader header, std::vector<unsigned char>& prog_data)
	{
		// copy existing data
		std::vector<unsigned char> prog_data_temp;

		UInt64 entrypoint = Utils::UInt64ToLittleEndian(header.entrypoint_idx);
		unsigned char* entrypoint_bytes = (unsigned char*)& entrypoint;
		for (size_t i = 0; i < sizeof(entrypoint); i++)
		{
			prog_data_temp.push_back(entrypoint_bytes[i]);
		}
		// file.write((char*)& entrypoint, sizeof(entrypoint));

		UInt64 comment_size = Utils::UInt64ToLittleEndian(header.file_comment.length());
		unsigned char* comment_size_bytes = (unsigned char*)& comment_size;
		for (size_t i = 0; i < sizeof(comment_size); i++)
		{
			prog_data_temp.push_back(comment_size_bytes[i]);
		}

		for (size_t i = 0; i < header.file_comment.length(); i++)
		{
			prog_data_temp.push_back(header.file_comment[i]);
		}
		// file.write((char*)& comment_size, sizeof(comment_size));
		// file.write(header.file_comment.c_str(), header.file_comment.length());

		for (auto c : prog_data)
		{
			prog_data_temp.push_back(c);
		}

		prog_data = prog_data_temp;
	}
}