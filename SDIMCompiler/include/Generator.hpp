#pragma once

#include <Types.hpp>
#include <vector>

// Interface to Generator backends to generate multiple different types of files such as exes, elf files and sdim bytecode files
// if I decide to generate native code then this might need a serious redesign
namespace SDIM
{
	class Generator
	{
	public:
		Generator() {}
		virtual ~Generator() {}

		/// Unconditional Jump Instruction
		/// Recommended use is for while loops and if statements specifically ones with else statements
		virtual void WriteJumpInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteCallInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;

		virtual void WritePushUInt8Instruction(std::vector<unsigned char>& prog_data,	UInt8 value) = 0;
		virtual void WritePushUInt16Instruction(std::vector<unsigned char>& prog_data,	UInt16 value) = 0;
		virtual void WritePushUInt32Instruction(std::vector<unsigned char>& prog_data,	UInt32 value) = 0;
		virtual void WritePushUInt64Instruction(std::vector<unsigned char>& prog_data,	UInt64 value) = 0;

		virtual void WritePushInt8Instruction(std::vector<unsigned char>& prog_data,	Int8 value) = 0;
		virtual void WritePushInt16Instruction(std::vector<unsigned char>& prog_data,	Int16 value) = 0;
		virtual void WritePushInt32Instruction(std::vector<unsigned char>& prog_data,	Int32 value) = 0;
		virtual void WritePushInt64Instruction(std::vector<unsigned char>& prog_data,	Int64 value) = 0;
		
		virtual void WritePushF32Instruction(std::vector<unsigned char>& prog_data,		F32 value) = 0;
		virtual void WritePushF64Instruction(std::vector<unsigned char>& prog_data,		F64 value) = 0;

		virtual void WriteHaltInstruction(std::vector<unsigned char>& prog_data) = 0;
	};
}