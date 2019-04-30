#include "Instructions.hpp"

#include "Utils.hpp"

#include <cassert>
namespace SDIM
{
	namespace Instructions
	{
		void PushReturnAddress(VMState& state, UInt64 addr)
		{
			state.ret_addrs_.push(addr);

		}
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

			const UInt64 opcode_offset = opcode_size + sizeof(func_addr);
			
			SDIM::Utils::Log("Called function at address: ", func_addr, " Previous address: ", state.program_counter_);
			PushReturnAddress(state, state.program_counter_ + opcode_offset);
			state.program_counter_ = func_addr;
			
			// size of opcode + 64 bit address
			// state.program_counter_ += opcode_size + sizeof(func_addr);
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
				(void)discard;
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
				(void)discard;
				state.program_counter_ += opcode_size;
			}
		
		}
		void Return(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Return");
			if (state.ret_addrs_.empty())
			{
				Utils::Log("Attempting to return with empty return address stack");
				state.running_ = false;
				return;
			}
			UInt64 ret_addr = state.ret_addrs_.top();
			state.ret_addrs_.pop();
			state.program_counter_ = ret_addr;
		
		}
		void JumpTrue(SDIM::VMState& state)
		{
			UInt64 jump_addr = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);

			const UInt64 opcode_offset = opcode_size + sizeof(jump_addr);

			if (SDIM::IsTrue(state.program_stack_.Pop()))
			{
				state.program_counter_ = jump_addr;
			}
			else
			{
				state.program_counter_ += opcode_offset;
			}
		}
		void JumpFalse(SDIM::VMState& state)
		{
			UInt64 jump_addr = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);

			const UInt64 opcode_offset = opcode_size + sizeof(jump_addr);

			if (SDIM::IsFalse(state.program_stack_.Pop()))
			{
				state.program_counter_ = jump_addr;
			}
			else
			{
				state.program_counter_ += opcode_offset;
			}
		}
		void CallTrue(SDIM::VMState& state)
		{
			
			UInt64 func_addr = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);

			const UInt64 opcode_offset = opcode_size + sizeof(func_addr);
			
			if (SDIM::IsTrue(state.program_stack_.Pop()))
			{
				PushReturnAddress(state, UInt64(state.program_counter_ + opcode_offset));
				
				state.program_counter_ = func_addr;
			}
			else
			{
				state.program_counter_ += opcode_offset;
			}
		}
		void CallFalse(SDIM::VMState& state)
		{
			UInt64 func_addr = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);

			const UInt64 opcode_offset = opcode_size + sizeof(func_addr);

			if (SDIM::IsFalse(state.program_stack_.Pop()))
			{
				PushReturnAddress(state, UInt64(state.program_counter_ + opcode_offset));
				state.program_counter_ = func_addr;
			}
			else
			{
				state.program_counter_ += opcode_offset;
			}
		}
		void CallTrueStack(SDIM::VMState& state)
		{
			

			const UInt64 opcode_offset = opcode_size;

			if (SDIM::IsTrue(state.program_stack_.Pop()))
			{
				SDIM::Variable var = state.program_stack_.Pop();
				assert("Call address in CallTrueStack must be of type UInt64" && var.type == VariableType::UInt64);
				UInt64 func_addr = var.as.uint64;

				PushReturnAddress(state, UInt64(state.program_counter_ + opcode_offset));
				state.program_counter_ = func_addr;
			}
			else
			{
				SDIM::Variable var = state.program_stack_.Pop();
				assert("Call address in CallTrueStack must be of type UInt64" && var.type == VariableType::UInt64);

				state.program_counter_ += opcode_offset;
			}
		}
		void CallFalseStack(SDIM::VMState& state)
		{
			const UInt64 opcode_offset = opcode_size;

			if (SDIM::IsFalse(state.program_stack_.Pop()))
			{
				SDIM::Variable var = state.program_stack_.Pop();
				assert("Call address in CallTrueStack must be of type UInt64" && var.type == VariableType::UInt64);
				UInt64 func_addr = var.as.uint64;

				
				PushReturnAddress(state, UInt64(state.program_counter_ + opcode_offset));
				state.program_counter_ = func_addr;
			}
			else
			{
				SDIM::Variable var = state.program_stack_.Pop();
				assert("Call address in CallTrueStack must be of type UInt64" && var.type == VariableType::UInt64);

				state.program_counter_ += opcode_offset;
			}
		}
		void NativeCall(SDIM::VMState& state)
		{
			// TODO: how to call C++ functions?
			// could have functions stored in a table but that would impose a restriction on the function signature
			// How do other languages handle this? Lua restricts you to a set function signature, chaiscript allows any signature
			// try to aim for the chaiscript style
			(void)state;
		}
		void Less(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Less");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Less with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Less(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void LessEqual(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("LessEqual");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted LessEqual with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::LessEqual(lhs, rhs));

			state.program_counter_ += opcode_size;
		}
		void Greater(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Greater");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Greater with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Greater(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void GreaterEqual(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("GreaterEqual");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted GreaterEqual with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::GreaterEqual(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Equal(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Equal");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Equal with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Equal(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void NotEqual(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("NotEqual");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted NotEqual with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::NotEqual(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Not(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Not");
			if (state.program_stack_.Size() < 1)
			{
				SDIM::Utils::Log("Attempted Not with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Not(lhs));

			state.program_counter_ += opcode_size;
		}

		void And(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("And");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted And with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::And(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Or(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Or");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Or with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Or(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Xor(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Xor");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Xor with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Xor(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Add(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Add");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Add with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Add(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Subtract(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Subtract");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Subtract with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Subtract(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void Multiply(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Multiply");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Multiply with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Multiply(lhs, rhs));

			state.program_counter_ += opcode_size;
		}

		void BitwiseNot(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("BitwiseNot");
			if (state.program_stack_.Size() < 1)
			{
				SDIM::Utils::Log("Attempted BitwiseNot with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::BitwiseNot(lhs));

			state.program_counter_ += opcode_size;
		}

		void Divide(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Divide");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Divide with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Divide(lhs, rhs));

			state.program_counter_ += opcode_size;

		}

		void Negate(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Negate");
			if (state.program_stack_.Size() < 1)
			{
				SDIM::Utils::Log("Attempted Negate with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Negate(lhs));

			state.program_counter_ += opcode_size;

		}

		void Modulo(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("Modulo");
			if (state.program_stack_.Size() < 2)
			{
				SDIM::Utils::Log("Attempted Modulo with: ", state.program_stack_.Size(), " elements");
				state.program_counter_ += opcode_size;
			}
			SDIM::Variable rhs = state.program_stack_.Pop();
			SDIM::Variable lhs = state.program_stack_.Pop();

			state.program_stack_.Push(Operators::Modulo(lhs, rhs));

			state.program_counter_ += opcode_size;

		}

		void PushInt8(SDIM::VMState& state)
		{
			Int8 val = Utils::ReadInt8Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt8: ", val));

			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushInt16(SDIM::VMState& state)
		{
			Int16 val = Utils::ReadInt16Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt16: ", val));

			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushInt32(SDIM::VMState& state)
		{
			Int32 val = Utils::ReadInt32Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt32: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushInt64(SDIM::VMState& state)
		{
			Int64 val = Utils::ReadInt64Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushInt64: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt8(SDIM::VMState& state)
		{
			UInt8 val = Utils::ReadUInt8Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt8: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt16(SDIM::VMState& state)
		{
			UInt16 val = Utils::ReadUInt16Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt16: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt32(SDIM::VMState& state)
		{
			UInt32 val = Utils::ReadUInt32Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt32: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushUInt64(SDIM::VMState& state)
		{
			UInt64 val = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushUInt64: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushF32(SDIM::VMState& state)
		{
			F32 val = Utils::UInt32ToF32(Utils::ReadUInt32Literal(state, state.program_counter_ + 1));
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushF32: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushF64(SDIM::VMState& state)
		{
			F64 val = Utils::UInt64ToF64(Utils::ReadUInt64Literal(state, state.program_counter_ + 1));
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushF64: ", val));
			state.program_stack_.Push(SDIM::Variable(val));
			state.program_counter_ += opcode_size + sizeof(val);
		}

		void PushPointer(SDIM::VMState& state)
		{
			void* ptr = Utils::UInt64ToPtr(Utils::ReadUInt64Literal(state, state.program_counter_ + 1));
			SDIM::Utils::Disassemble(SDIM::Utils::ConstructString("PushPointer: ", ptr));
			state.program_stack_.Push(SDIM::Variable(ptr));
			state.program_counter_ += opcode_size + sizeof(ptr);
		}

		void PushString(SDIM::VMState& state)
		{
			SDIM::Utils::Disassemble("PushString");
			UInt64 len = Utils::ReadUInt64Literal(state, state.program_counter_ + 1);
			Utils::Log("PushString with length ", len);
			UInt64 str_start_offset = sizeof(UInt64) + 1;
			// TODO: stop this leaking memory somehow
			char* str;
			str = new char[len];
			std::memset(str, 0, len);
			for (UInt64 i = 0; i < len; i++)
			{
				
				str[i] = Utils::ReadInt8Literal(state, i + state.program_counter_ + str_start_offset);
				
			}
			
			state.program_stack_.Push(SDIM::Variable(str));
			state.program_counter_ += str_start_offset + len;
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
			
			state.program_stack_.Push(SDIM::Variable((UInt64)state.program_stack_.Size()));
			state.program_counter_ += opcode_size;
		}

		void Halt(SDIM::VMState & state)
		{
			SDIM::Utils::Disassemble("Halt");
			state.running_ = false;
		}
		
	}
}