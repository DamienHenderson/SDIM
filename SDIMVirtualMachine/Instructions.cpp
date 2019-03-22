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

		size_t LessEqual(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Greater(Stack & prog_stack)
		{
			return size_t();
		}

		size_t GreaterEqual(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Equal(Stack & prog_stack)
		{
			return size_t();
		}

		size_t NotEqual(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Not(Stack & prog_stack)
		{
			return size_t();
		}

		size_t And(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Or(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Xor(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Add(Stack & prog_stack)
		{
			if (prog_stack.Size() < 2)
			{
				SDIM::Utils::Log("Attemped add with: ", prog_stack.Size(), " elements");
				return opcode_size;
			}
			SDIM::Variable rhs = prog_stack.Pop();
			SDIM::Variable lhs = prog_stack.Pop();

			// no need to cast/promote types
			if (rhs.type == lhs.type)
			{
				VarUnion var_un;
				if (lhs.type == VariableType::UInt16)
				{
					var_un.uint16 = lhs.as.uint16 + rhs.as.uint16;
				}
				prog_stack.Push(SDIM::Variable(lhs.type, var_un));
			}
			return opcode_size;
		}

		size_t Subtract(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Multiply(Stack & prog_stack)
		{
			return size_t();
		}

		size_t BitwiseNot(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Divide(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Negate(Stack & prog_stack)
		{
			return size_t();
		}

		size_t Modulo(Stack & prog_stack)
		{
			return size_t();
		}

		size_t PushInt8(Stack & prog_stack, Int8 val)
		{
			VarUnion var_un;
			var_un.int8 = val;
			SDIM::Variable var{ VariableType::Int8, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushInt16(Stack & prog_stack, Int16 val)
		{
			VarUnion var_un;
			var_un.int16 = val;
			SDIM::Variable var{ VariableType::Int16, var_un};
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushInt32(Stack & prog_stack, Int32 val)
		{
			VarUnion var_un;
			var_un.int32 = val;
			SDIM::Variable var{ VariableType::Int32, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushInt64(Stack & prog_stack, Int64 val)
		{
			VarUnion var_un;
			var_un.int64 = val;
			SDIM::Variable var{ VariableType::Int64, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt8(Stack & prog_stack, UInt8 val)
		{
			VarUnion var_un;
			var_un.uint8 = val;
			SDIM::Variable var{ VariableType::UInt8, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt16(Stack & prog_stack, UInt16 val)
		{
			VarUnion var_un;
			var_un.uint16 = val;
			SDIM::Variable var{ VariableType::UInt16, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt32(Stack & prog_stack, UInt32 val)
		{
			VarUnion var_un;
			var_un.uint32 = val;
			SDIM::Variable var{ VariableType::UInt32, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt64(Stack & prog_stack, UInt64 val)
		{
			VarUnion var_un;
			var_un.uint64 = val;
			SDIM::Variable var{ VariableType::UInt64, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushF32(Stack & prog_stack, F32 val)
		{
			VarUnion var_un;
			var_un.f32 = val;
			SDIM::Variable var{ VariableType::F32, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushF64(Stack & prog_stack, F64 val)
		{
			VarUnion var_un;
			var_un.f64 = val;
			SDIM::Variable var{ VariableType::F64, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushPointer(Stack & prog_stack, void * ptr)
		{
			VarUnion var_un;
			var_un.ptr = ptr;
			SDIM::Variable var{ VariableType::Pointer, var_un };
			prog_stack.Push(var);
			return opcode_size + sizeof(ptr);
		}

		size_t PushString(Stack & prog_stack)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushStruct(Stack & prog_stack)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushClass(Stack & prog_stack)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t LocalVar(Stack & prog_stack)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t Pop(Stack & prog_stack)
		{
			prog_stack.Pop();
			return opcode_size;
		}

		size_t PushLocal(Stack & prog_stack)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushAddr(Stack & prog_stack)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t Break()
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushStackCount(Stack & prog_stack)
		{
			VarUnion var_un;
			var_un.uint64 = (UInt64)prog_stack.Size();
			SDIM::Variable var{ VariableType::UInt64, var_un };
			prog_stack.Push(var);
			return opcode_size;
		}
		
	}
}