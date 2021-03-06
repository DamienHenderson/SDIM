#pragma once

#include <Types.hpp>
#include <vector>

// Interface to Generator backends to generate multiple different types of files such as exes, elf files and sdim bytecode files
// if I decide to generate native code then this might need a serious redesign
namespace SDIM
{
	enum class GeneratorType
	{
		BytecodeGenerator
	};
	class Generator
	{
	public:
		Generator() {}
		virtual ~Generator() {}

		/// Unconditional Jump Instruction
		/// Recommended use is for while loops and if statements specifically ones with else statements
		virtual void WriteJumpInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteJumpTrueInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteJumpFalseInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteJumpTrueStackInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteJumpFalseStackInstruction(std::vector<unsigned char>& prog_data) = 0;
		
		virtual void WriteCallInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteCallTrueInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteCallFalseInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) = 0;
		virtual void WriteCallTrueStackInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteCallFalseStackInstruction(std::vector<unsigned char>& prog_data) = 0;

		virtual void WriteReturnInstruction(std::vector<unsigned char>& prog_data) = 0;

		

		/// TODO: what args should this take, also on native platforms this should probably just do a normal call
		// virtual void WriteNativeCall Instruction(std::vector<unsigned char>& prog_data) = 0;
		// Logical Operators
		virtual void WriteLessInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteLessEqualInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteGreaterInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteGreaterEqualInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteEqualInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteNotEqualInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteNotInstruction(std::vector<unsigned char>& prog_data) = 0;
		// Bitwise Operators
		virtual void WriteAndInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteOrInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteXorInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteBitwiseNotInstruction(std::vector<unsigned char>& prog_data) = 0;
		// Arithmetic Operators
		virtual void WriteAddInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteSubtractInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteMultiplyInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteDivideInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteNegateInstruction(std::vector<unsigned char>& prog_data) = 0;
		virtual void WriteModuloInstruction(std::vector<unsigned char>& prog_data) = 0;
		


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

		virtual void WritePushStringInstruction(std::vector<unsigned char>& prog_data, const char* value) = 0;

		virtual void WritePushLocalInstruction(std::vector<unsigned char>& prog_data, UInt64 idx) = 0;
		
		virtual void WriteLocalVarInstruction(std::vector<unsigned char>& prog_data, UInt64 idx) = 0;

		virtual void WriteVMCallInstruction(std::vector<unsigned char>& prog_data, UInt64 idx) = 0;

		virtual void WriteHaltInstruction(std::vector<unsigned char>& prog_data) = 0;

		virtual GeneratorType GetType() const = 0;
	};
}