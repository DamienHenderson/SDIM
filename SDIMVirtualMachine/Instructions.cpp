#include "Instructions.hpp"

#include "Utils.hpp"
namespace SDIM
{
	namespace Instructions
	{
		void NoOperation(SDIM::VMState& state)
		{
			SDIM::Utils::Log("NoOperation");
			state.program_counter_ += opcode_size;
		}
		void VMCall(SDIM::VMState& state)
		{

			UInt64 func_id = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("VMCall: ", func_id));
			// TODO: Call VM functions here
			if (func_id == 1)
			{
				state.program_stack_.PrintStackTop();
			}
			// size of opcode + size of func id
			state.program_counter_ += opcode_size + sizeof(func_id);
		}
		void Call(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Call");
			UInt64 func_addr = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Log("Called function at address: ", func_addr, " Previous address: ", state.program_counter_);
			SDIM::VarUnion var_un;
			var_un.uint64 = state.program_counter_ + opcode_size + sizeof(func_addr);
			state.program_stack_.Push(SDIM::Variable(SDIM::VariableType::UInt64, var_un));
			state.program_counter_ = func_addr;
			
			// size of opcode + 64 bit address
			state.program_counter_ += opcode_size + sizeof(func_addr);
		}
		void Jump(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Jump");
			UInt64 jump_addr = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);
			// size of opcode + 64 bit address
			state.program_counter_ = jump_addr;
			
		}
		void JumpStack(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("JumpStack");
			SDIM::Variable var = state.program_stack_.Pop();
			if (var.type != VariableType::UInt64)
			{
				SDIM::Utils::Log("Jump targets must be of type UInt64");
				state.program_counter_ += opcode_size;
			}
			state.program_counter_ = var.as.uint64;
			
			
		}
		void JumpTrueStack(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("JumpTrueStack");
			SDIM::Variable cond = state.program_stack_.Pop();
			if (SDIM::IsTrue(cond))
			{
				SDIM::Variable var = state.program_stack_.Pop();
				if (var.type != VariableType::UInt64)
				{
					SDIM::Utils::Log("Jump targets must be of type UInt64");
					state.program_counter_ += opcode_size;
				}
				state.program_counter_ = var.as.uint64;
			}
			else
			{
				SDIM::Variable discard = state.program_stack_.Pop();
				state.program_counter_ += opcode_size;
			}
			
		}
		void JumpFalseStack(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("JumpFalseStack");
			SDIM::Variable cond = state.program_stack_.Pop();
			if (SDIM::IsFalse(cond))
			{
				SDIM::Variable var = state.program_stack_.Pop();
				if (var.type != VariableType::UInt64)
				{
					SDIM::Utils::Log("Jump targets must be of type UInt64");
					state.program_counter_ += opcode_size;
				}
				state.program_counter_ = var.as.uint64;
			}
			else
			{
				SDIM::Variable discard = state.program_stack_.Pop();
				state.program_counter_ += opcode_size;
			}
		
		}
		void Return(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Return");
			SDIM::Variable ret_addr = state.program_stack_.Pop();
			if (ret_addr.type != VariableType::UInt64)
			{
				SDIM::Utils::Log("state.program_counter_ += targets must be of type UInt64");
				state.program_counter_ += opcode_size;
			}
			state.program_counter_ = ret_addr.as.uint64;
		
		}
		void JumpTrue(SDIM::VMState& state, UInt64 address)
		{
			
		}
		void JumpFalse(SDIM::VMState& state, UInt64 address)
		{
			
		}
		void CallTrue(SDIM::VMState& state, UInt64 address)
		{
			
		}
		void CallFalse(SDIM::VMState& state, UInt64 address)
		{
			
		}
		void CallTrueStack(SDIM::VMState& state)
		{
			
		}
		void CallFalseStack(SDIM::VMState& state)
		{
			
		}
		void NativeCall(SDIM::VMState& state)
		{
			
		}
		void Less(SDIM::VMState& state)
		{

			
		}

		void LessEqual(SDIM::VMState& state)
		{

		}
		void Greater(SDIM::VMState& state)
		{
			
		}

		void GreaterEqual(SDIM::VMState& state)
		{
			
		}

		void Equal(SDIM::VMState& state)
		{
			
		}

		void NotEqual(SDIM::VMState& state)
		{
			
		}

		void Not(SDIM::VMState& state)
		{
			
		}

		void And(SDIM::VMState& state)
		{
			
		}

		void Or(SDIM::VMState& state)
		{
			
		}

		void Xor(SDIM::VMState& state)
		{
			
		}

		void Add(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Add");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attemped add with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
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
			state.program_counter_ += opcode_size;
		}

		void Subtract(SDIM::VMState& state)
		{
			
		}

		void Multiply(SDIM::VMState& state)
		{
			
		}

		void BitwiseNot(SDIM::VMState& state)
		{
			
		}

		void Divide(SDIM::VMState& state)
		{
			
		}

		void Negate(SDIM::VMState& state)
		{
			
		}

		void Modulo(SDIM::VMState& state)
		{
			
		}

		void PushInt8(SDIM::VMState& state)
		{
			Int8 val = Utils::ReadInt8Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt8: ", val));
			VarUnion var_un;
			var_un.int8 = val;
			SDIM::Variable var{ VariableType::Int8, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushInt16(SDIM::VMState& state)
		{
			Int16 val = Utils::ReadInt16Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt16: ", val));
			VarUnion var_un;
			var_un.int16 = val;
			SDIM::Variable var{ VariableType::Int16, var_un};
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushInt32(SDIM::VMState& state)
		{
			Int32 val = Utils::ReadInt32Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt32: ", val));
			VarUnion var_un;
			var_un.int32 = val;
			SDIM::Variable var{ VariableType::Int32, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushInt64(SDIM::VMState& state)
		{
			Int64 val = Utils::ReadInt64Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt64: ", val));
			VarUnion var_un;
			var_un.int64 = val;
			SDIM::Variable var{ VariableType::Int64, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt8(SDIM::VMState& state)
		{
			UInt8 val = Utils::ReadUInt8Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt8: ", val));
			VarUnion var_un;
			var_un.uint8 = val;
			SDIM::Variable var{ VariableType::UInt8, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt16(SDIM::VMState& state)
		{
			UInt16 val = Utils::ReadUInt16Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt16: ", val));
			VarUnion var_un;
			var_un.uint16 = val;
			SDIM::Variable var{ VariableType::UInt16, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt32(SDIM::VMState& state)
		{
			UInt32 val = Utils::ReadUInt32Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt32: ", val));
			VarUnion var_un;
			var_un.uint32 = val;
			SDIM::Variable var{ VariableType::UInt32, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt64(SDIM::VMState& state)
		{
			UInt64 val = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt64: ", val));
			VarUnion var_un;
			var_un.uint64 = val;
			SDIM::Variable var{ VariableType::UInt64, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushF32(SDIM::VMState& state)
		{
			F32 val = Utils::UInt32ToF32(Utils::ReadUInt32Literal(state, state.program_counter_ + 1));
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushF32: ", val));
			VarUnion var_un;
			var_un.f32 = val;
			SDIM::Variable var{ VariableType::F32, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushF64(SDIM::VMState& state)
		{
			F64 val = Utils::UInt64ToF64(Utils::ReadUInt64Literal(state, state.program_counter_ + 1));
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushF64: ", val));
			VarUnion var_un;
			var_un.f64 = val;
			SDIM::Variable var{ VariableType::F64, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushPointer(SDIM::VMState& state)
		{
			void* ptr = Utils::UInt64ToPtr(Utils::ReadUInt64Literal(state, state.program_counter_ + 1));
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushPointer: ", ptr));
			VarUnion var_un;
			var_un.ptr = ptr;
			SDIM::Variable var{ VariableType::Pointer, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size + sizeof(ptr);
		}

		void PushString(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushString");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void PushStruct(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushStruct");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void PushClass(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushClass");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void LocalVar(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("LocalVar");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void Pop(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Pop");
			state.program_stack_.Pop();
			state.program_counter_ += opcode_size;
		}

		void PushLocal(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushLocal");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void PushAddr(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushAddr");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void Break(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Break");
			// not implemented yet
			state.program_counter_ += opcode_size;
		}

		void PushStackCount(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushStackCount");
			VarUnion var_un;
			var_un.uint64 = (UInt64)state.program_stack_.Size();
			SDIM::Variable var{ VariableType::UInt64, var_un };
			state.program_stack_.Push(var);
			state.program_counter_ += opcode_size;
		}

		void Halt(SDIM::VMState & state)
		{
			SDIM::Utils::Disassemble("Halt");
			state.running_ = false;
		}
		
	}
}