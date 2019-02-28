#include "VirtualMachine.hpp"

#include <fstream>
#include <iostream>

namespace SDIM
{
	VirtualMachine::VirtualMachine()
	{
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
			std::cerr << "Failed to open file at path: " << path << "\n";
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

			// TODO: Optimise this as a big switch usually isn't optimal
			switch (next_instruction)
			{
			case Instruction::NOP:
				std::cerr << "No Operation\n";
				AdvanceInstructionPointer();
				return true;
			case Instruction::VMCall:
			{	
				// For now VMCall with argument 1 is Print the top of the stack
				AdvanceInstructionPointer();
				UInt64 func_id = ReadUInt64Literal();
				if (func_id == 1)
				{
					PrintStackTop();
					std::cout << "Print Stack Top called\n";
				}
				return true;
			}
			
			case Instruction::Add:
				AdvanceInstructionPointer();
				AddStack();
				std::cout << "Add Stack\n";
				return true;
			case Instruction::PushUInt16:
			{
				AdvanceInstructionPointer();
				UInt16 literal_value = ReadUInt16Literal();
				Variable var;
				var.type = VariableType::UInt16;
				var.as.uint16 = literal_value;
				PushVariable(var);

				std::cout << "Pushed UInt16 " << var.as.uint16 << "\n";
				return true;
			}
			case Instruction::Halt:
				std::cerr << "Halt Reached\n";
				return false;
				
			default:
			
				std::cerr << "Unknown Opcode: " << static_cast<UInt8>(next_instruction) << "\n";
				AdvanceInstructionPointer();
				return false;
			
			}

		}
		return false;
	}

	

}