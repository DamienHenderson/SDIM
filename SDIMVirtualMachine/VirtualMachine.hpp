#pragma once

#include "Types.hpp"
#include "Utils.hpp"
#include "Instructions.hpp"
#include "Stack.hpp"

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

		inline void AdvanceInstructionPointer(size_t offset) { instruction_pointer_ += offset; }
		// Reads a UInt64 literal in little endian format
		// TODO: read literal without adjusting instruction pointer
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

		
		// Adds the top two variables on the stack pops them and pushes the result
		void AddStack()
		{
			if (stack_.Size() < 2)
			{
				SDIM::Utils::Log("Not enough items on stack to add ", stack_.Size(), "Expected ", 2);
				return;
			}

			
			SDIM::Variable var_rhs = stack_.Pop();
			SDIM::Variable var_lhs = stack_.Pop();
			
			if (var_lhs.type == VariableType::UInt16 && var_rhs.type == VariableType::UInt16)
			{
				Variable result;
				result.type = VariableType::UInt16;
				result.as.uint16 = var_lhs.as.uint16 + var_rhs.as.uint16;

				stack_.Push(result);
			}

		}
		

		SDIM::Stack stack_;

		SDIM::Variable accumulator; // optimisation, might not be needed

		bool running_{ false };
	};

}

