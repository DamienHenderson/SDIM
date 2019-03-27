#pragma once

#include "Types.hpp"
#include "Utils.hpp"
#include "Instructions.hpp"
#include "Stack.hpp"
#include "VMState.hpp"


#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <functional>

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
		
		
		VMState state_;
		// Returns false if an error occurs
		bool ExecuteNextOpcode();

		void PrintState();
		
		Instruction ReadNextInstruction();

		std::array<std::function<void(SDIM::VMState&)>, MAX_OPCODES> opcode_table_;
	};

}

