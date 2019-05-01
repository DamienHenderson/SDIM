#pragma once

#include "Types.hpp"

namespace SDIM
{
	class Stack
	{
	public:
		Stack();
		~Stack();

		/// Push a variable onto the top of the stack
		void Push(const SDIM::Variable& data);
		
		/// Pop the top of the stack
		SDIM::Variable Pop();

		/// Look at the top of the stack without popping it
		SDIM::Variable Peek() const;

		/// Resize the stack to count elements copying existing data across
		/// If the new stack is smaller the data will be copied from the bottom end of the stack
		/// Returns false on allocation failure
		bool Resize(size_t count);

		/// Returns whether or not the stack is empty
		bool Empty() const;

		/// Returns the maximum number of elements the stack can hold currently
		size_t Capacity() const;

		/// Returns the number of elements in the stack
		size_t Size() const;

		SDIM::Variable GetVariable(size_t idx);

		void SetVariable(Variable var, size_t idx);

		void PrintStackTop() const;

		void PrintStack() const;
	private:

		SDIM::Variable* data_{ nullptr };
		size_t stack_capacity_{0};
		size_t stack_top_{0};

	};
}
