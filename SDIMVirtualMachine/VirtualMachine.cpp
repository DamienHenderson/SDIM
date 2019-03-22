#include "VirtualMachine.hpp"

#include <fstream>
#include <iostream>

namespace SDIM
{
	
	VirtualMachine::VirtualMachine()
	{
		// 32k Variables 
		// profile this to see if it's a good starting value
		stack_.Resize(32768);
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
		program_length_ = file_data.size();

		instruction_pointer_ = program_data_;

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
		if (program_data_ != nullptr && instruction_pointer_ != nullptr)
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
		if (instruction_pointer_ != nullptr)
		{
			Instruction next_instruction = static_cast<Instruction>(static_cast<UInt8>(*instruction_pointer_));
#ifdef SDIMVM_DEBUG
			stack_.PrintStack();
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
				AdvanceInstructionPointer(1);
				UInt64 func_id = ReadUInt64Literal();
				size_t offset = SDIM::Instructions::VMCall(stack_, func_id);
				
				// For now VMCall with argument 1 is Print the top of the stack
				// AdvanceInstructionPointer();
				/*
				if (func_id == 1)
				{
					stack_.PrintStackTop();
					SDIM::Utils::Log("Print Stack Top called");
				}
				*/
				return true;
			}
			
			case Instruction::Add:
				AdvanceInstructionPointer(1);
				Instructions::Add(stack_);
				SDIM::Utils::Log("Add Stack");
				return true;
			case Instruction::PushUInt16:
			{
				AdvanceInstructionPointer(1);
				UInt16 literal_value = ReadUInt16Literal();
				Instructions::PushUInt16(stack_, literal_value);
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