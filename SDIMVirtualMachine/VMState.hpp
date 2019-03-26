#pragma once

#include "Stack.hpp"
namespace SDIM
{
	struct VMState
	{
		size_t program_counter_{ 0 };
		size_t program_length_{ 0 };
		Stack program_stack_;
	};
}