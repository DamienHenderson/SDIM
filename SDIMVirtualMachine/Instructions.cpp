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
		size_t VMCall(SDIM::VMState& state, UInt64 func_id)
		{
			// TODO: Call VM functions here
			if (func_id == 1)
			{
				state.program_stack_.PrintStackTop();
			}
			// size of opcode + size of func id
			return opcode_size + sizeof(func_id);
		}
		size_t Call(SDIM::VMState& state, UInt64 func_addr)
		{
			SDIM::Utils::Log("Called function at address: ", func_addr, " Previous address: ", state.program_counter_);
			SDIM::VarUnion var_un;
			var_un.uint64 = state.program_counter_ + opcode_size + sizeof(func_addr);
			state.program_stack_.Push(SDIM::Variable(SDIM::VariableType::UInt64, var_un));
			state.program_counter_ = func_addr;
			
			// size of opcode + 64 bit address
			return opcode_size + sizeof(func_addr);
		}
		size_t Jump(SDIM::VMState& state, UInt64 jump_addr)
		{
			// size of opcode + 64 bit address
			state.program_counter_ = jump_addr;
			return opcode_size + sizeof(jump_addr);
		}
		size_t JumpStack(SDIM::VMState& state)
		{
			
			SDIM::Variable var = state.program_stack_.Pop();
			if (var.type != VariableType::UInt64)
			{
				SDIM::Utils::Log("Jump targets must be of type UInt64");
				return opcode_size;
			}
			state.program_counter_ = var.as.uint64;
			// no immediate value
			return opcode_size;
		}
		size_t JumpTrueStack(SDIM::VMState& state)
		{
			SDIM::Variable cond = state.program_stack_.Pop();
			if (SDIM::IsTrue(cond))
			{
				SDIM::Variable var = state.program_stack_.Pop();
				if (var.type != VariableType::UInt64)
				{
					SDIM::Utils::Log("Jump targets must be of type UInt64");
					return opcode_size;
				}
				state.program_counter_ = var.as.uint64;
			}
			else
			{
				SDIM::Variable discard = state.program_stack_.Pop();
			}
			// no immediate value
			return opcode_size;
		}
		size_t JumpFalseStack(SDIM::VMState& state)
		{
			SDIM::Variable cond = state.program_stack_.Pop();
			if (SDIM::IsFalse(cond))
			{
				SDIM::Variable var = state.program_stack_.Pop();
				if (var.type != VariableType::UInt64)
				{
					SDIM::Utils::Log("Jump targets must be of type UInt64");
					return opcode_size;
				}
				state.program_counter_ = var.as.uint64;
			}
			else
			{
				SDIM::Variable discard = state.program_stack_.Pop();
			}
			// no immediate value
			return opcode_size;
		}
		size_t Return(SDIM::VMState& state)
		{
			SDIM::Variable ret_addr = state.program_stack_.Pop();
			if (ret_addr.type != VariableType::UInt64)
			{
				SDIM::Utils::Log("Return targets must be of type UInt64");
				return opcode_size;
			}
			state.program_counter_ = ret_addr.as.uint64;
			// technically unnecessary as the opcode jumps back to a stored instruction address
			return opcode_size;
		}
		size_t JumpTrue(SDIM::VMState& state, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t JumpFalse(SDIM::VMState& state, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t CallTrue(SDIM::VMState& state, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t CallFalse(SDIM::VMState& state, UInt64 address)
		{
			// opcode + size of immediate address
			return opcode_size + sizeof(address);
		}
		size_t CallTrueStack(SDIM::VMState& state)
		{
			// opcode size
			return opcode_size;
		}
		size_t CallFalseStack(SDIM::VMState& state)
		{
			// opcode size
			return opcode_size;
		}
		size_t NativeCall(SDIM::VMState& state)
		{
			// opcode size as necessary information is stored on the stack
			return opcode_size;
		}
		size_t Less(SDIM::VMState& state)
		{

			return opcode_size;
		}

		size_t LessEqual(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Greater(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t GreaterEqual(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Equal(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t NotEqual(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Not(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t And(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Or(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Xor(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Add(SDIM::VMState& state)
		{
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attemped add with: ", state.program_stack_.Size(), " elements");
				return opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			// no need to cast/promote types
			if (rhs.type == lhs.type)
			{
				VarUnion var_un;
				if (lhs.type == VariableType::UInt16)
				{
					var_un.uint16 = lhs.as.uint16 + rhs.as.uint16;
				}
				state.program_stack_.Push(SDIM::Variable(lhs.type, var_un));
			}
			return opcode_size;
		}

		size_t Subtract(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Multiply(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t BitwiseNot(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Divide(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Negate(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t Modulo(SDIM::VMState& state)
		{
			return size_t();
		}

		size_t PushInt8(SDIM::VMState& state, Int8 val)
		{
			VarUnion var_un;
			var_un.int8 = val;
			SDIM::Variable var{ VariableType::Int8, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushInt16(SDIM::VMState& state, Int16 val)
		{
			VarUnion var_un;
			var_un.int16 = val;
			SDIM::Variable var{ VariableType::Int16, var_un};
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushInt32(SDIM::VMState& state, Int32 val)
		{
			VarUnion var_un;
			var_un.int32 = val;
			SDIM::Variable var{ VariableType::Int32, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushInt64(SDIM::VMState& state, Int64 val)
		{
			VarUnion var_un;
			var_un.int64 = val;
			SDIM::Variable var{ VariableType::Int64, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt8(SDIM::VMState& state, UInt8 val)
		{
			VarUnion var_un;
			var_un.uint8 = val;
			SDIM::Variable var{ VariableType::UInt8, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt16(SDIM::VMState& state, UInt16 val)
		{
			VarUnion var_un;
			var_un.uint16 = val;
			SDIM::Variable var{ VariableType::UInt16, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt32(SDIM::VMState& state, UInt32 val)
		{
			VarUnion var_un;
			var_un.uint32 = val;
			SDIM::Variable var{ VariableType::UInt32, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushUInt64(SDIM::VMState& state, UInt64 val)
		{
			VarUnion var_un;
			var_un.uint64 = val;
			SDIM::Variable var{ VariableType::UInt64, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushF32(SDIM::VMState& state, F32 val)
		{
			VarUnion var_un;
			var_un.f32 = val;
			SDIM::Variable var{ VariableType::F32, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushF64(SDIM::VMState& state, F64 val)
		{
			VarUnion var_un;
			var_un.f64 = val;
			SDIM::Variable var{ VariableType::F64, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(val);
		}

		size_t PushPointer(SDIM::VMState& state, void * ptr)
		{
			VarUnion var_un;
			var_un.ptr = ptr;
			SDIM::Variable var{ VariableType::Pointer, var_un };
			state.program_stack_.Push(var);
			return opcode_size + sizeof(ptr);
		}

		size_t PushString(SDIM::VMState& state)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushStruct(SDIM::VMState& state)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushClass(SDIM::VMState& state)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t LocalVar(SDIM::VMState& state)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t Pop(SDIM::VMState& state)
		{
			state.program_stack_.Pop();
			return opcode_size;
		}

		size_t PushLocal(SDIM::VMState& state)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushAddr(SDIM::VMState& state)
		{
			// not implemented yet
			return opcode_size;
		}

		size_t Break()
		{
			// not implemented yet
			return opcode_size;
		}

		size_t PushStackCount(SDIM::VMState& state)
		{
			VarUnion var_un;
			var_un.uint64 = (UInt64)state.program_stack_.Size();
			SDIM::Variable var{ VariableType::UInt64, var_un };
			state.program_stack_.Push(var);
			return opcode_size;
		}
		
	}
}