#pragma once

#include "Types.hpp"

#include "Stack.hpp"

#include "VMState.hpp"
namespace SDIM
{

	

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