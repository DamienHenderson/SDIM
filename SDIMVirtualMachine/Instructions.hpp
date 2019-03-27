#pragma once

#include "Types.hpp"

#include "Stack.hpp"

#include "VMState.hpp"
namespace SDIM
{

	constexpr size_t opcode_size = 1;
	/// TODO: Find a better place for this to be shared between the Compiler and VM
	enum class Instruction : UInt8
	{
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

	};
	// number of allowed single byte opcodes
	constexpr size_t MAX_OPCODES = 256;

	namespace Instructions
	{
		/// Opcode functions
		/// return value is void which is the amount to move the instruction pointer in bytes

		/// immediate refers to literal values in little endian format embedded in the bytecode file

		/// TODO: make a variable stack object to pass by reference into these functions
		/// to allow the state of the vm stack to be modified 

		/// Perform no action for this instruction
		void NoOperation(SDIM::VMState& state);

		/// Call built in utilities in the VM
		void VMCall(SDIM::VMState& state);

		/// Call immediate address
		void Call(SDIM::VMState& state);

		/// Jump to immediate address
		void Jump(SDIM::VMState& state);

		/// Jump to the address at stack[top]
		void JumpStack(SDIM::VMState& state);

		/// Jump to the address at stack[top - 1] if stack[top] is true
		void JumpTrueStack(SDIM::VMState& state);

		/// Jump to the address at stack[top - 1] if stack[top] is false
		void JumpFalseStack(SDIM::VMState& state);

		/// Returns from function call
		void Return(SDIM::VMState& state);

		/// Jumps to immediate address if stack[top] is true
		void JumpTrue(SDIM::VMState& state);

		/// Jumps to immediate address if stack[top] is false
		void JumpFalse(SDIM::VMState& state);

		/// Call function at immediate address if stack[top] is true
		void CallTrue(SDIM::VMState& state);

		/// Call function at immediate address if stack[top] is false
		void CallFalse(SDIM::VMState& state);

		/// Call function at stack[top - 1] if stack[top] is true
		void CallTrueStack(SDIM::VMState& state);

		/// Call function at stack[top - 1] if stack[top] is false
		void CallFalseStack(SDIM::VMState& state);

		/// Call registered native function with provided name
		void NativeCall(SDIM::VMState& state);

		/// Performs Boolean operation stack[top - 1] < stack[top] and pushes result as UInt8
		void Less(SDIM::VMState& state);

		void LessEqual(SDIM::VMState& state);

		void Greater(SDIM::VMState& state);
		
		void GreaterEqual(SDIM::VMState& state);

		void Equal(SDIM::VMState& state);
			
		void NotEqual(SDIM::VMState& state);
			
		void Not(SDIM::VMState& state);
			
		void And(SDIM::VMState& state);
			
		void Or(SDIM::VMState& state);
			
		void Xor(SDIM::VMState& state);

		void Add(SDIM::VMState& state);
			
		void Subtract(SDIM::VMState& state);

		void Multiply(SDIM::VMState& state);
		
		void BitwiseNot(SDIM::VMState& state);

		void Divide(SDIM::VMState& state);
			
		void Negate(SDIM::VMState& state);
			
		void Modulo(SDIM::VMState& state);
			
		void PushInt8(SDIM::VMState& state);
			
		void PushInt16(SDIM::VMState& state);
			
		void PushInt32(SDIM::VMState& state);

		void PushInt64(SDIM::VMState& state);
			
		void PushUInt8(SDIM::VMState& state);
		
		void PushUInt16(SDIM::VMState& state);
			
		void PushUInt32(SDIM::VMState& state);
			
		void PushUInt64(SDIM::VMState& state);
			
		void PushF32(SDIM::VMState& state);
			
		void PushF64(SDIM::VMState& state);

		void PushPointer(SDIM::VMState& state);
		
		void PushString(SDIM::VMState& state);

		void PushStruct(SDIM::VMState& state);
			
		void PushClass(SDIM::VMState& state);
			
		void LocalVar(SDIM::VMState& state);
			
		void Pop(SDIM::VMState& state);
			
		void PushLocal(SDIM::VMState& state);

		void PushAddr(SDIM::VMState& state);

		void Break(SDIM::VMState& state);
			
		void PushStackCount(SDIM::VMState& state);
			
		// void Dump();
			
		// void Error();
			
		void Halt(SDIM::VMState& state);
			
		// void Pause();
			
		// void PushInfoString();
	}
}