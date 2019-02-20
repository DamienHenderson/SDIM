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
	}

	bool VirtualMachine::LoadFile(const std::string & path)
	{
		std::fstream file(path, std::ios::in | std::ios::binary);

		if (!file.good())
		{
			std::cerr << "Failed to open file at path: " << path << "\n";
			return false;
		}



	}

	bool VirtualMachine::RunFile()
	{
		if (program_data_ != nullptr && instruction_pointer_ != nullptr)
		{
			running_ = true;
			while (running_)
			{
				bool res = ExecuteNextOpcode();
			}
		}
		return false;
	}

	bool VirtualMachine::ExecuteNextOpcode()
	{
		if (instruction_pointer_ != nullptr)
		{
			Instruction next_instruction = static_cast<Instruction>(static_cast<UInt8>(*instruction_pointer_));

			switch (next_instruction)
			{
			case Instruction::NOP:
				std::cerr << "No Operation\n";
				AdvanceInstructionPointer();
				return true;
			default:
			
				std::cerr << "Unknown Opcode: " << static_cast<UInt8>(next_instruction) << "\n";
				return false;
			
			}

		}
		return false;
	}

	

}