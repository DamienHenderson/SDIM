#pragma once

#include "Types.hpp"
#include "Utils.hpp"
#include "Instructions.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace SDIM
{
	
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

