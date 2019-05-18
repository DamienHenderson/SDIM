#pragma once

#include <vector>

#include "Types.hpp"
namespace SDIM
{
	class VariableStorage
	{
	public:
		VariableStorage() {}
		~VariableStorage() {}
		/// Get the value in a specific variable slot
		SDIM::Variable GetVariable(size_t idx);
		/// Set the value of a variable in a specific var storage slot
		void SetVariable(size_t idx, const SDIM::Variable& var);
		/// Resize the Variable Storage
		void Resize(size_t count);
		/// Adds the specified variable to the next available slot after the current top
		void PushVariable(const SDIM::Variable& var);

		/// Returns the current top of the Variable storage
		SDIM::Variable PopVariable();
		

	private:
		std::vector<SDIM::Variable> variables_;
		size_t top_idx_{ 0 };
	};
}