#include "Stack.hpp"

#include "Utils.hpp"

namespace SDIM
{
	Stack::Stack()
	{
	}


	Stack::~Stack()
	{
		delete[] data_;
	}

	void Stack::Push(const SDIM::Variable & var)
	{
		if (stack_top_ + 1 >= stack_capacity_)
		{
			SDIM::Utils::Log("Resizing stack to accomodate push");
			Resize(static_cast<size_t>(stack_capacity_ * 1.5f));
		}
		data_[stack_top_++] = var;
	}
	SDIM::Variable Stack::Pop()
	{
		if (Empty())
		{
			SDIM::Utils::Log("Attempting to Pop from an empty stack");
			return SDIM::Variable();
		}
		return data_[--stack_top_];
	}
	SDIM::Variable Stack::Peek() const
	{
		if (Empty())
		{
			SDIM::Utils::Log("Attempting to Peek an empty stack");
			return SDIM::Variable();
		}
		return data_[stack_top_ - 1];
	}
	bool Stack::Resize(size_t count)
	{
		SDIM::Variable* new_stack_ptr = new SDIM::Variable[count];
		if (new_stack_ptr != nullptr)
		{
			if (data_ != nullptr)
			{
				delete[] data_;
			}
			data_ = new_stack_ptr;
			stack_capacity_ = count;
			return true;
		}
		return false;
	}
	bool Stack::Empty() const
	{
		return stack_top_ == 0;
	}
	size_t Stack::Capacity() const
	{
		return stack_capacity_;
	}
	size_t Stack::Size() const
	{
		return stack_capacity_;
	}
}