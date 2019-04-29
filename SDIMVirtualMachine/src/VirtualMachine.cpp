#include "VirtualMachine.hpp"

#include <fstream>
#include <iostream>
#include "Types.hpp"
#include "Utils.hpp"
// #include "Types.hpp"


namespace SDIM
{
	
	VirtualMachine::VirtualMachine()
	{
		// 32k stack Variables 
		// profile this to see if it's a good starting value
		state_.program_stack_.Resize(32768);
		// 16k variable storage
		// profile this to see if it's a good starting value
		// this is used for the semi register based nature of the language
		state_.variables_.Resize(16384);
		
		// Put all of the opcode handler functions into the opcode table
		PopulateOpcodeTable();
		
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

		UInt64 entrypoint = Utils::ReadUInt64Literal(file_data, 0);

		UInt64 comment_size = Utils::ReadUInt64Literal(file_data, sizeof(entrypoint));
		std::string file_comment{ "" };
		UInt64 comment_offset = sizeof(entrypoint) + sizeof(comment_size);
		for (UInt64 i = 0; i < comment_size; i++)
		{
			file_comment += file_data[i + comment_offset];
		}
		Utils::Log(file_comment);
		UInt64 header_size = comment_offset + comment_size;

		state_.program_data_ = new char[file_data.size() - header_size];
		std::memcpy(state_.program_data_, file_data.data() + header_size, file_data.size() - header_size);
		state_.program_length_ = file_data.size();

		state_.program_counter_ = entrypoint;

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
#ifdef SDIM_VERBOSE
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

	void VirtualMachine::PopulateOpcodeTable()
	{
		for (size_t i = 0; i < MAX_OPCODES; i++)
		{
			// fill opcode table with NoOperation to avoid errors when calling opcodes which may not have been implemented
			opcode_table_[i] = SDIM::Instructions::NoOperation;
		}

		/*
		NOP = 0x00,
		VMCall = 0x01,
		Call = 0x02,
		Jmp = 0x03,
		JmpStack = 0x04,
		JmpTStack = 0x05,
		JmpFStack = 0x06,
		Return = 0x07,
		JmpT = 0x08,
		JmpF = 0x09,
		CallT = 0x0A,
		CallF = 0x0B,
		CallTStack = 0x0C,
		CallFStack = 0x0D,
		NativeCall = 0x0E,
		Less = 0x0F,
		LessEqual = 0x10,
		Greater = 0x11,
		GreaterEqual = 0x12,
		Equal = 0x13,
		NotEqual = 0x14,
		Not = 0x15,
		And = 0x16, // Bitwise AND not logical AND
		Or = 0x17,  // Bitwise OR not logical OR
		Xor = 0x18, // Bitwise XOR not logical XOR
		Add = 0x19,
		Subtract = 0x1A,
		Multiply = 0x1B,
		BitwiseNot = 0x1C,
		Divide = 0x1D,
		Negate = 0x1E,
		Modulo = 0x1F,
		PushInt8 = 0x20,
		PushInt16 = 0x21,
		PushInt32 = 0x22,
		PushInt64 = 0x23,
		PushUInt8 = 0x24,
		PushUInt16 = 0x25,
		PushUInt32 = 0x26,
		PushUInt64 = 0x27,
		PushF32 = 0x28,
		PushF64 = 0x29,
		PushPointer = 0x2A,
		PushString = 0x2B,
		PushStruct = 0x2C,
		PushClass = 0x2D,
		LocalVar = 0x2E,
		Pop = 0x2F,
		PushLocal = 0x30,

		PushAddr = 0x41,
		Break = 0x42,
		PushStackCount = 0x43,
		Dump = 0x44,
		Error = 0x45,
		Halt = 0x48,
		Pause = 0x50,
		PushInfoString = 0x53
		*/
		opcode_table_[static_cast<UInt8>(Instruction::VMCall)] = Instructions::VMCall;
		opcode_table_[static_cast<UInt8>(Instruction::Call)] = Instructions::Call;
		opcode_table_[static_cast<UInt8>(Instruction::Jmp)] = Instructions::Jump;
		opcode_table_[static_cast<UInt8>(Instruction::JmpStack)] = Instructions::JumpStack;
		opcode_table_[static_cast<UInt8>(Instruction::JmpTStack)] = Instructions::JumpTrueStack;
		opcode_table_[static_cast<UInt8>(Instruction::JmpFStack)] = Instructions::JumpFalseStack;
		opcode_table_[static_cast<UInt8>(Instruction::Return)] = Instructions::Return;
		opcode_table_[static_cast<UInt8>(Instruction::JmpT)] = Instructions::JumpTrue;
		opcode_table_[static_cast<UInt8>(Instruction::JmpF)] = Instructions::JumpFalse;
		opcode_table_[static_cast<UInt8>(Instruction::CallT)] = Instructions::CallTrue;
		opcode_table_[static_cast<UInt8>(Instruction::CallF)] = Instructions::CallFalse;
		opcode_table_[static_cast<UInt8>(Instruction::CallTStack)] = Instructions::CallTrueStack;
		opcode_table_[static_cast<UInt8>(Instruction::CallFStack)] = Instructions::CallFalseStack;
		opcode_table_[static_cast<UInt8>(Instruction::NativeCall)] = Instructions::NativeCall;

		opcode_table_[static_cast<UInt8>(Instruction::Less)] = Instructions::Less;
		opcode_table_[static_cast<UInt8>(Instruction::LessEqual)] = Instructions::LessEqual;
		opcode_table_[static_cast<UInt8>(Instruction::Greater)] = Instructions::Greater;
		opcode_table_[static_cast<UInt8>(Instruction::GreaterEqual)] = Instructions::GreaterEqual;
		opcode_table_[static_cast<UInt8>(Instruction::Equal)] = Instructions::Equal;
		opcode_table_[static_cast<UInt8>(Instruction::NotEqual)] = Instructions::NotEqual;
		opcode_table_[static_cast<UInt8>(Instruction::Not)] = Instructions::Not;
		opcode_table_[static_cast<UInt8>(Instruction::And)] = Instructions::And;
		opcode_table_[static_cast<UInt8>(Instruction::Or)] = Instructions::Or;
		opcode_table_[static_cast<UInt8>(Instruction::Xor)] = Instructions::Xor;
		opcode_table_[static_cast<UInt8>(Instruction::Add)] = Instructions::Add;
		opcode_table_[static_cast<UInt8>(Instruction::Subtract)] = Instructions::Subtract;
		opcode_table_[static_cast<UInt8>(Instruction::Multiply)] = Instructions::Multiply;
		opcode_table_[static_cast<UInt8>(Instruction::BitwiseNot)] = Instructions::BitwiseNot;
		opcode_table_[static_cast<UInt8>(Instruction::Divide)] = Instructions::Divide;
		opcode_table_[static_cast<UInt8>(Instruction::Negate)] = Instructions::Negate;
		opcode_table_[static_cast<UInt8>(Instruction::Modulo)] = Instructions::Modulo;
		
		opcode_table_[static_cast<UInt8>(Instruction::PushUInt8)] = Instructions::PushUInt8;
		opcode_table_[static_cast<UInt8>(Instruction::PushUInt16)] = Instructions::PushUInt16;
		opcode_table_[static_cast<UInt8>(Instruction::PushUInt32)] = Instructions::PushUInt32;
		opcode_table_[static_cast<UInt8>(Instruction::PushUInt64)] = Instructions::PushUInt64;

		opcode_table_[static_cast<UInt8>(Instruction::PushInt8)] = Instructions::PushInt8;
		opcode_table_[static_cast<UInt8>(Instruction::PushInt16)] = Instructions::PushInt16;
		opcode_table_[static_cast<UInt8>(Instruction::PushInt32)] = Instructions::PushInt32;
		opcode_table_[static_cast<UInt8>(Instruction::PushInt64)] = Instructions::PushInt64;

		opcode_table_[static_cast<UInt8>(Instruction::PushF32)] = Instructions::PushF32;
		opcode_table_[static_cast<UInt8>(Instruction::PushF64)] = Instructions::PushF64;

		opcode_table_[static_cast<UInt8>(Instruction::PushPointer)] = Instructions::PushPointer;
		// not implemented yet
		opcode_table_[static_cast<UInt8>(Instruction::PushString)] = Instructions::PushString;
		opcode_table_[static_cast<UInt8>(Instruction::PushStruct)] = Instructions::PushStruct;
		opcode_table_[static_cast<UInt8>(Instruction::PushClass)] = Instructions::PushClass;
		opcode_table_[static_cast<UInt8>(Instruction::LocalVar)] = Instructions::LocalVar;
		
		opcode_table_[static_cast<UInt8>(Instruction::Pop)] = Instructions::Pop;
		opcode_table_[static_cast<UInt8>(Instruction::PushLocal)] = Instructions::PushLocal;
		// Debugging utilities
		opcode_table_[static_cast<UInt8>(Instruction::PushAddr)] = Instructions::PushAddr;
		opcode_table_[static_cast<UInt8>(Instruction::Break)] = Instructions::Break;
		opcode_table_[static_cast<UInt8>(Instruction::PushStackCount)] = Instructions::PushStackCount;
		// opcode_table_[static_cast<UInt8>(Instruction::Dump)] = Instructions::Dump;
		// opcode_table_[static_cast<UInt8>(Instruction::Error)] = Instructions::Error;
		opcode_table_[static_cast<UInt8>(Instruction::Halt)] = Instructions::Halt;
		// opcode_table_[static_cast<UInt8>(Instruction::Pause)] = Instructions::Pause;
		// opcode_table_[static_cast<UInt8>(Instruction::PushInfoString)] = Instructions::PushInfoString;
			
			
			
		
	}

	Instruction VirtualMachine::ReadNextInstruction()
	{
		return static_cast<Instruction>(static_cast<UInt8>(state_.program_data_[state_.program_counter_]));
		
	}

	

}