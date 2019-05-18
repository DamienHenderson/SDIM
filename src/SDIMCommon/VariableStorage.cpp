#include "VariableStorage.hpp"

#include <cassert>
namespace SDIM
{
	SDIM::Variable VariableStorage::GetVariable(size_t idx)
	{
		return variables_.at(idx);
	}

	void VariableStorage::SetVariable(size_t idx, const SDIM::Variable& var)
	{
		variables_.at(idx) = var;
	}

	void VariableStorage::Resize(size_t count)
	{
		variables_.resize(count);
	}

	void VariableStorage::PushVariable(const SDIM::Variable& var)
	{
		if (top_idx_ >= variables_.size())
		{
			/// Need to resize
			Resize(variables_.size() * 2);
		}

		variables_.at(top_idx_++) = var;
	}

	SDIM::Variable VariableStorage::PopVariable()
	{
		if (top_idx_ <= 0)
		{
			// No variables in the variable storage
			// Return an empty variable but assert here so it fails in debug builds
			assert("Attempting to pop variable from empty variable storage" && false);
			return SDIM::Variable();
		}
		return variables_[--top_idx_];
	}
}