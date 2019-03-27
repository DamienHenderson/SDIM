#include "VirtualMachine.hpp"

#include <fstream>
#include <iostream>

namespace SDIM
{
	
	VirtualMachine::VirtualMachine()
	{
		// 32k Variables 
		// profile this to see if it's a good starting value
		state_.program_stack_.Resize(32768);

		for (size_t i = 0; i < MAX_OPCODES; i++)
		{
			// fill opcode table with NoOperation
			opcode_table_[i] = SDIM::Instructions::NoOperation;
		}

		opcode_table_[static_cast<UInt8>(Instruction::VMCall)] = Instructions::VMCall;
		opcode_table_[static_cast<UInt8>(Instruction::Add)] = Instructions::Add;
		opcode_table_[static_cast<UInt8>(Instruction::PushUInt16)] = Instructions::PushUInt16;
		opcode_table_[static_cast<UInt8>(Instruction::Halt)] = Instructions::Halt;
	}


	VirtualMachine::~VirtualMachine()
	{
		if (state_.program_data_ != nullptr)
		{
			delete[] state_.program_data_;
		}
	}

	bool VirtualMachine::LoadFile(const std::string & path)
	{
		std::fstream file(path, std::ios::in | std::ios::binary);

		if (!file.good())
		{
			SDIM::Utils::Log("Failed to open file at path: ", path);
			return false;
		}

		std::vector<char> file_data(std::istreambuf_iterator<char>(file), {});
		state_.program_data_ = new char[file_data.size()];
		std::memcpy(state_.program_data_, file_data.data(), file_data.size());
		state_.program_length_ = file_data.size();

		state_.program_counter_ = 0;

		return true;
	}

	bool VirtualMachine::RunFile()
	{
		if (SDIM::Utils::IsLittleEndian())
		{
			SDIM::Utils::Log("Platform endianness is little endian");
		}
		else
		{
			SDIM::Utils::Log("Platform endianness is big endian");
		}
		if (state_.program_data_ != nullptr)
		{
			state_.running_ = true;
			while (state_.running_)
			{
				bool res = ExecuteNextOpcode();

				if (!res)
				{
					// TODO: Error Handling
					state_.running_ = false;
				}
			}
		}
		return true;
	}

	bool VirtualMachine::ExecuteNextOpcode()
	{
		if (state_.program_counter_ < state_.program_length_)
		{
			Instruction next_instruction = ReadNextInstruction();
#ifdef SDIMVM_DEBUG
			PrintState();
#endif
			opcode_table_[static_cast<UInt8>(next_instruction)](state_);
			return true;

		}
		return false;
	}

	void VirtualMachine::PrintState()
	{
		SDIM::Utils::Log("Program Data: ", std::string(state_.program_data_, state_.program_length_));
		SDIM::Utils::Log("Program Length: ", state_.program_length_);
		SDIM::Utils::Log("Program Counter: ", state_.program_counter_);
		
		state_.program_stack_.PrintStack();
	}

	Instruction VirtualMachine::ReadNextInstruction()
	{
		return static_cast<Instruction>(static_cast<UInt8>(state_.program_data_[state_.program_counter_]));
		
	}

	

}