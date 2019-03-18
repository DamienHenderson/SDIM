#pragma once

#include "Types.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace SDIM
{
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
	class VirtualMachine
	{
	public:
		VirtualMachine();
		~VirtualMachine();

		bool LoadFile(const std::string& path);

		// Run the file which is currently loaded into memory
		bool RunFile();

	private: 
		char* program_data_{ nullptr };
		char* instruction_pointer_{ nullptr };

		size_t program_length_{ 0 };
		
		// Returns false if an error occurs
		bool ExecuteNextOpcode();

		inline void AdvanceInstructionPointer() { instruction_pointer_ += 1; }
		// Reads a UInt64 literal in little endian format
		UInt64 ReadUInt64Literal()
		{
			UInt64 literal_value{ 0 };

			for (int i = 0; i < sizeof(literal_value); i++)
			{
				unsigned char read_byte = static_cast<unsigned char>(*(instruction_pointer_++));
				literal_value |= read_byte << (i * 8);
			}
			
			return literal_value;
		}

		UInt16 ReadUInt16Literal()
		{
			UInt16 literal_value{ 0 };

			for (int i = 0; i < sizeof(literal_value); i++)
			{
				UInt8 read_byte = static_cast<UInt8>(*(instruction_pointer_++));
				literal_value |= read_byte << (i * 8);
			}

			return literal_value;
		}

		void PrintStackTop()
		{
			if (stack_.empty())
			{
				std::cerr << "Stack is empty during call to print stack top\n";
				return;
			}

			SDIM::Variable var = stack_[--stack_top_];

			SDIM::Utils::LogIntermediate("Top of stack: ");
			switch (var.type)
			{
			case VariableType::UInt8:
				SDIM::Utils::Log(var.as.uint8);
				break;
			case VariableType::UInt16:
				SDIM::Utils::Log(var.as.uint16);
				break;
			case VariableType::UInt32:
				SDIM::Utils::Log(var.as.uint32);
				break;
			case VariableType::UInt64:
				SDIM::Utils::Log(var.as.uint64);
				break;

			case VariableType::Int8:
				SDIM::Utils::Log(var.as.int8);
				break;
			case VariableType::Int16:
				SDIM::Utils::Log(var.as.int16);
				break;
			case VariableType::Int32:
				SDIM::Utils::Log(var.as.int32);
				break;
			case VariableType::Int64:
				SDIM::Utils::Log(var.as.int64);
				break;

			case VariableType::F32:
				SDIM::Utils::Log(var.as.f32);
				break;
			case VariableType::F64:
				SDIM::Utils::Log(var.as.f64);
				break;
			
			case VariableType::Pointer:
				SDIM::Utils::Log(var.as.ptr);
				break;

			default:
				SDIM::Utils::Log("Unknown Var Type");
				break;
			}
		}
		// Adds the top two variables on the stack pops them and pushes the result
		void AddStack()
		{
			if (stack_.size() < 2)
			{
				SDIM::Utils::Log("Not enough items on stack to add ", stack_.size());
				return;
			}

			Variable var_rhs = stack_[--stack_top_];
			stack_.pop_back();
			Variable var_lhs = stack_[--stack_top_];
			stack_.pop_back();
			
			if (var_lhs.type == VariableType::UInt16 && var_rhs.type == VariableType::UInt16)
			{
				Variable result;
				result.type = VariableType::UInt16;
				result.as.uint16 = var_lhs.as.uint16 + var_rhs.as.uint16;

				PushVariable(result);
			}

		}
		SDIM::Variable PopStack()
		{
			if (stack_.empty())
			{
				SDIM::Utils::Log("Stack is empty at attempt to pop variable");
				return SDIM::Variable();
			}

			return stack_[--stack_top_];
		}
		void PushVariable(Variable var)
		{
			stack_.push_back(var);
			++stack_top_;
		}
		// TODO: Use actual stack here
		std::vector<SDIM::Variable> stack_;

		size_t stack_top_{ 0 };

		SDIM::Variable accumulator; // optimisation, might not be needed

		bool running_{ false };
	};

}

