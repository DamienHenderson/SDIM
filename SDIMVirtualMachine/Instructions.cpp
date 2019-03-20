#include "Instructions.hpp"

#include "Utils.hpp"
namespace SDIM
{
	size_t NoOperation()
	{
		SDIM::Utils::Log("NoOperation");
		return opcode_size;
	}
	size_t VMCall(UInt64 func_id)
	{
		// TODO: Call VM functions here

		// size of opcode + size of func id
		return opcode_size + sizeof(UInt64);
	}
	size_t Call(UInt64 func_addr)
	{
		// size of opcode + 64 bit address
		return opcode_size + sizeof(UInt64);
	}
	size_t Jump(UInt64 jump_addr)
	{
		// size of opcode + 64 bit address
		return opcode_size + sizeof(UInt64);
	}
	size_t JumpStack(Stack & prog_stack)
	{
		return size_t();
	}
	size_t JumpTrueStack(Stack & prog_stack)
	{
		return size_t();
	}
	size_t JumpFalseStack(Stack & prog_stack)
	{
		return size_t();
	}
	size_t Return(Stack & prog_stack)
	{
		return size_t();
	}
	size_t JumpTrue(Stack & prog_stack, UInt64 address)
	{
		return size_t();
	}
	size_t JumpFalse(Stack & prog_stack, UInt64 address)
	{
		return size_t();
	}
	size_t CallTrue(Stack & prog_stack, UInt64 address)
	{
		return size_t();
	}
	size_t CallFalse(Stack & prog_stack, UInt64 address)
	{
		return size_t();
	}
	size_t CallTrueStack(Stack & prog_stack, UInt64 address)
	{
		return size_t();
	}
	size_t CallFalseStack(Stack & prog_stack, UInt64 address)
	{
		return size_t();
	}
	size_t NativeCall(Stack & prog_stack)
	{
		return size_t();
	}
	size_t Less(Stack & prog_stack)
	{
		return size_t();
	}
	size_t JumpStack()
	{
		// size of opcode as this doesn't use an immediate value
		return opcode_size;
	}
	size_t JumpTrueStack()
	{
		return size_t();
	}
	size_t JumpFalseStack()
	{
		return size_t();
	}
	size_t Return()
	{
		return size_t();
	}
	size_t JumpTrue()
	{
		return size_t();
	}
	size_t JumpFalse()
	{
		return size_t();
	}
	size_t CallTrue()
	{
		return size_t();
	}
	size_t CallFalse()
	{
		return size_t();
	}
	size_t CallTrueStack()
	{
		return size_t();
	}
	size_t CallFalseStack()
	{
		return size_t();
	}
	size_t NativeCall()
	{
		return size_t();
	}
	size_t Less()
	{
		return size_t();
	}
	size_t Call()
	{
		return size_t();
	}
	size_t Jump()
	{
		return size_t();
	}
}