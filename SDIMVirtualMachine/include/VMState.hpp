#pragma once

#include "Stack.hpp"
#include "VariableStorage.hpp"
namespace SDIM
{
	struct VMState
	{
		char* program_data_{ nullptr };
		size_t program_counter_{ 0 };
		size_t program_length_{ 0 };
		Stack program_stack_;
		SDIM::Variable accumulator_; // optimisation, might not be needed
		SDIM::VariableStorage variables_;
		bool running_{ false };
	};

	namespace Utils
	{
		UInt8 ReadUInt8Literal(VMState& state, size_t location);

		UInt16 ReadUInt16Literal(VMState& state, size_t location);

		UInt32 ReadUInt32Literal(VMState& state, size_t location);

		UInt64 ReadUInt64Literal(VMState& state, size_t location);

		Int8 ReadInt8Literal(VMState& state, size_t location);

		Int16 ReadInt16Literal(VMState& state, size_t location);

		Int32 ReadInt32Literal(VMState& state, size_t location);

		Int64 ReadInt64Literal(VMState& state, size_t location);
	}
}