#pragma once

#include "Types.hpp"

#include "Stack.hpp"
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
	namespace Instructions
	{
		/// Opcode functions
		/// return value is size_t which is the amount to move the instruction pointer in bytes

		/// immediate refers to literal values in little endian format embedded in the bytecode file

		/// TODO: make a variable stack object to pass by reference into these functions
		/// to allow the state of the vm stack to be modified 

		/// Perform no action for this instruction
		size_t NoOperation();

		/// Call built in utilities in the VM
		size_t VMCall(Stack& stack, UInt64 func_id);

		/// Call immediate address
		size_t Call(UInt64 func_addr);

		/// Jump to immediate address
		size_t Jump(UInt64 jump_addr);

		/// Jump to the address at stack[top]
		size_t JumpStack(Stack& prog_stack);

		/// Jump to the address at stack[top - 1] if stack[top] is true
		size_t JumpTrueStack(Stack& prog_stack);

		/// Jump to the address at stack[top - 1] if stack[top] is false
		size_t JumpFalseStack(Stack& prog_stack);

		/// Returns from function call
		size_t Return(Stack& prog_stack);

		/// Jumps to immediate address if stack[top] is true
		size_t JumpTrue(Stack& prog_stack, UInt64 address);

		/// Jumps to immediate address if stack[top] is false
		size_t JumpFalse(Stack& prog_stack, UInt64 address);

		/// Call function at immediate address if stack[top] is true
		size_t CallTrue(Stack& prog_stack, UInt64 address);

		/// Call function at immediate address if stack[top] is false
		size_t CallFalse(Stack& prog_stack, UInt64 address);

		/// Call function at stack[top - 1] if stack[top] is true
		size_t CallTrueStack(Stack& prog_stack);

		/// Call function at stack[top - 1] if stack[top] is false
		size_t CallFalseStack(Stack& prog_stack);

		/// Call registered native function with provided name
		size_t NativeCall(Stack& prog_stack);

		/// Performs Boolean operation stack[top - 1] < stack[top] and pushes result as UInt8
		size_t Less(Stack& prog_stack);

		size_t LessEqual(Stack& prog_stack);

		size_t Greater(Stack& prog_stack);
		
		size_t GreaterEqual(Stack& prog_stack);

		size_t Equal(Stack& prog_stack);
			
		size_t NotEqual(Stack& prog_stack);
			
		size_t Not(Stack& prog_stack);
			
		size_t And(Stack& prog_stack);
			
		size_t Or(Stack& prog_stack);
			
		size_t Xor(Stack& prog_stack);

		size_t Add(Stack& prog_stack);
			
		size_t Subtract(Stack& prog_stack);

		size_t Multiply(Stack& prog_stack);
		
		size_t BitwiseNot(Stack& prog_stack);

		size_t Divide(Stack& prog_stack);
			
		size_t Negate(Stack& prog_stack);
			
		size_t Modulo(Stack& prog_stack);
			
		size_t PushInt8(Stack& prog_stack, Int8 val);
			
		size_t PushInt16(Stack& prog_stack, Int16 val);
			
		size_t PushInt32(Stack& prog_stack, Int32 val);

		size_t PushInt64(Stack& prog_stack, Int64 val);
			
		size_t PushUInt8(Stack& prog_stack, UInt8 val);
		
		size_t PushUInt16(Stack& prog_stack, UInt16 val);
			
		size_t PushUInt32(Stack& prog_stack, UInt32 val);
			
		size_t PushUInt64(Stack& prog_stack, UInt64 val);
			
		size_t PushF32(Stack& prog_stack, F32 val);
			
		size_t PushF64(Stack& prog_stack, F64 val);

		size_t PushPointer(Stack& prog_stack, void* ptr);
		
		size_t PushString(Stack& prog_stack);

		size_t PushStruct(Stack& prog_stack);
			
		size_t PushClass(Stack& prog_stack);
			
		size_t LocalVar(Stack& prog_stack);
			
		size_t Pop(Stack& prog_stack);
			
		size_t PushLocal(Stack& prog_stack);

		size_t PushAddr(Stack& prog_stack);

		size_t Break();
			
		size_t PushStackCount(Stack& prog_stack);
			
		// size_t Dump();
			
		// size_t Error();
			
		// size_t Halt();
			
		// size_t Pause();
			
		// size_t PushInfoString();
	}
}