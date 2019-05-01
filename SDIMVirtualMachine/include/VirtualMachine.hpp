#pragma once

#include "Instructions.hpp"
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

		// one way interop between SDIM and host application
		SDIM::Variable GetVariable(size_t idx);

	private: 
		
		
		VMState state_;
		// Returns false if an error occurs
		bool ExecuteNextOpcode();

		void PrintState();

		void PopulateOpcodeTable();
		
		Instruction ReadNextInstruction();

		std::array<std::function<void(SDIM::VMState&)>, MAX_OPCODES> opcode_table_;
	};

}

