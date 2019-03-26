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
	}


	VirtualMachine::~VirtualMachine()
	{
		if (program_data_ != nullptr)
		{
			delete[] program_data_;
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
		program_data_ = new char[file_data.size()];
		std::memcpy(program_data_, file_data.data(), file_data.size());
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
		if (program_data_ != nullptr)
		{
			running_ = true;
			while (running_)
			{
				bool res = ExecuteNextOpcode();

				if (!res)
				{
					// TODO: Error Handling
					running_ = false;
				}
			}
		}
		return true;
	}

	bool VirtualMachine::ExecuteNextOpcode()
	{
		if (state_.program_counter_ < state_.program_length_)
		{
			Instruction next_instruction = static_cast<Instruction>(static_cast<UInt8>(program_data_[state_.program_counter_]));
#ifdef SDIMVM_DEBUG
			state_.program_stack_.PrintStack();
#endif
			// TODO: Optimise this as a big switch usually isn't optimal
			// once all the functions are done i could make a function pointer table and address it with opcode ids
			switch (next_instruction)
			{
			case Instruction::NOP:
			{
				size_t offset = SDIM::Instructions::NoOperation();
				AdvanceInstructionPointer(offset);
				return true;
			}
			case Instruction::VMCall:
			{	
				
				UInt64 func_id = ReadUInt64Literal(state_.program_counter_ + 1);
				size_t offset = SDIM::Instructions::VMCall(state_, func_id);
				AdvanceInstructionPointer(offset);
				
				return true;
			}
			
			case Instruction::Add:
				AdvanceInstructionPointer(1);
				Instructions::Add(state_);
				SDIM::Utils::Log("Add Stack");
				return true;
			case Instruction::PushUInt16:
			{
				
				UInt16 literal_value = ReadUInt16Literal(state_.program_counter_ + 1);
				size_t offset = Instructions::PushUInt16(state_, literal_value);
				AdvanceInstructionPointer(offset);
				return true;
			}
			case Instruction::Halt:
				SDIM::Utils::Log("Halt Reached");
				return false;
				
			default:
			
				SDIM::Utils::Log("Unknown Opcode: ", static_cast<UInt8>(next_instruction));
				AdvanceInstructionPointer(1);
				return false;
			
			}

		}
		return false;
	}

	

}