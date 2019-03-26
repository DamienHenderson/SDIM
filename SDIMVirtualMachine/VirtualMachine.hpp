#pragma once

#include "Types.hpp"
#include "Utils.hpp"
#include "Instructions.hpp"
#include "Stack.hpp"
#include "VMState.hpp"


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
		// size_t program_counter_{ 0 };

		// size_t program_length_{ 0 };
		
		VMState state_;
		// Returns false if an error occurs
		bool ExecuteNextOpcode();

		inline void AdvanceInstructionPointer(size_t offset) { state_.program_counter_ += offset; }
		// Reads a UInt64 literal in little endian format
		// TODO: read literal without adjusting instruction pointer
		UInt64 ReadUInt64Literal(size_t location)
		{
			UInt64 literal_value{ 0 };
			if ((location + sizeof(literal_value) - 1) > state_.program_length_)
			{
				SDIM::Utils::Log("Attempt to read immediate value which would read past the end of the program data");
				return literal_value;
			}
			for (int i = 0; i < sizeof(literal_value); i++)
			{
				unsigned char read_byte = static_cast<unsigned char>(program_data_[location + i]);
				literal_value |= read_byte << (i * 8);
			}
			
			return literal_value;
		}

		UInt16 ReadUInt16Literal(size_t location)
		{
			UInt16 literal_value{ 0 };
			if ((location + sizeof(literal_value) - 1) > state_.program_length_)
			{
				SDIM::Utils::Log("Attempt to read immediate value which would read past the end of the program data");
				return literal_value;
			}
			for (int i = 0; i < sizeof(literal_value); i++)
			{
				UInt8 read_byte = static_cast<unsigned char>(program_data_[location + i]);
				literal_value |= read_byte << (i * 8);
			}

			return literal_value;
		}

		SDIM::Variable accumulator; // optimisation, might not be needed

		bool running_{ false };
	};

}

