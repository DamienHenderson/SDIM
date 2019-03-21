#include "Instructions.hpp"

#include "Utils.hpp"
namespace SDIM
{
	namespace Instructions
	{
		size_t NoOperation()
		{
			SDIM::Utils::Log("NoOperation");
			return opcode_size;
		}
		size_t VMCall(Stack& stack, UInt64 func_id)
		{
			// TODO: Call VM functions here
			if (func_id == 1)
			{
				stack.PrintStackTop();
			}
			// size of opcode + size of func id
			return opcode_size + sizeof(func_id);
		}
		size_t Call(UInt64 func_addr)
		{
			// size of opcode + 64 bit address
			return opcode_size + sizeof(func_addr);
		}
		size_t Jump(UInt64 jump_addr)
		{
			// size of opcode + 64 bit address
			return opcode_size + sizeof(jump_addr);
		}
		size_t JumpStack(Stack & prog_stack)
		{
			// no immediate value
			return opcode_size;
		}
		size_t JumpTrueStack(Stack & prog_stack)
		{
			// no immediate value
			return opcode_size;
		}
		size_t JumpFalseStack(Stack & prog_stack)
		{
			// no immediate value
			return opcode_size;
		}
		size_t Return(Stack & prog_stack)
		{
			// technically unnecessary as the opcode jumps back to a stored instruction address
			return opcode_size;
		}
		size_t JumpTrue(Stack & prog_stack, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t JumpFalse(Stack & prog_stack, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t CallTrue(Stack & prog_stack, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t CallFalse(Stack & prog_stack, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t CallTrueStack(Stack & prog_stack)
		{
			// opcode size
			return opcode_size;
		}
		size_t CallFalseStack(Stack & prog_stack)
		{
			// opcode size
			return opcode_size;
		}
		size_t NativeCall(Stack & prog_stack)
		{
			// opcode size as necessary information is stored on the stack
			return opcode_size;
		}
		size_t Less(Stack & prog_stack)
		{

			return opcode_size;
		}
		
	}
}