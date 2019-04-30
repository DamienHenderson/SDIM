#pragma once

#include "Generator.hpp"

#include <string>
#include <vector>
namespace SDIM
{
	/// NOTE: this is not to be directly written to the bytecode file
	/// instead a function should be used to write this
	struct BytecodeHeader
	{
		UInt64 entrypoint_idx{ 0 };
		std::string file_comment{ "Compiled SDIM Bytecode file" }; // encoded as a UInt64 length followed by the string
	};
	void WriteBytecodeHeader(BytecodeHeader header, std::vector<unsigned char>& prog_data);
	class BytecodeGenerator : public Generator
	{
	public:
		BytecodeGenerator() : Generator() {}
		virtual ~BytecodeGenerator() {}

		virtual void WriteJumpInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) override;
		virtual void WriteJumpTrueInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) override;
		virtual void WriteJumpFalseInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) override;
		virtual void WriteJumpTrueStackInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteJumpFalseStackInstruction(std::vector<unsigned char>& prog_data) override;

		virtual void WriteCallInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) override;
		virtual void WriteCallTrueInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) override;
		virtual void WriteCallFalseInstruction(std::vector<unsigned char>& prog_data, UInt64 addr) override;
		virtual void WriteCallTrueStackInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteCallFalseStackInstruction(std::vector<unsigned char>& prog_data) override;

		virtual void WriteReturnInstruction(std::vector<unsigned char>& prog_data) override;

		// Logical Operators
		virtual void WriteLessInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteLessEqualInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteGreaterInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteGreaterEqualInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteEqualInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteNotEqualInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteNotInstruction(std::vector<unsigned char>& prog_data) override;
		// Bitwise Operators
		virtual void WriteAndInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteOrInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteXorInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteBitwiseNotInstruction(std::vector<unsigned char>& prog_data) override;
		// Arithmetic Operators
		virtual void WriteAddInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteSubtractInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteMultiplyInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteDivideInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteNegateInstruction(std::vector<unsigned char>& prog_data) override;
		virtual void WriteModuloInstruction(std::vector<unsigned char>& prog_data) override;

		virtual void WritePushUInt8Instruction(std::vector<unsigned char>& prog_data,	UInt8 value) override;
		virtual void WritePushUInt16Instruction(std::vector<unsigned char>& prog_data,	UInt16 value) override;
		virtual void WritePushUInt32Instruction(std::vector<unsigned char>& prog_data,	UInt32 value) override;
		virtual void WritePushUInt64Instruction(std::vector<unsigned char>& prog_data,	UInt64 value) override;

		virtual void WritePushInt8Instruction(std::vector<unsigned char>& prog_data,	Int8 value) override;
		virtual void WritePushInt16Instruction(std::vector<unsigned char>& prog_data,	Int16 value) override;
		virtual void WritePushInt32Instruction(std::vector<unsigned char>& prog_data,	Int32 value) override;
		virtual void WritePushInt64Instruction(std::vector<unsigned char>& prog_data,	Int64 value) override;

		virtual void WritePushF32Instruction(std::vector<unsigned char>& prog_data,		F32 value) override;
		virtual void WritePushF64Instruction(std::vector<unsigned char>& prog_data,		F64 value) override;

		virtual void WritePushStringInstruction(std::vector<unsigned char>& prog_data, const char* value) override;
		
		virtual void WriteHaltInstruction(std::vector<unsigned char>& prog_data) override;

		virtual GeneratorType GetType() const override;

		BytecodeHeader& GetHeader();
	private:
		BytecodeHeader header_;
	};
}