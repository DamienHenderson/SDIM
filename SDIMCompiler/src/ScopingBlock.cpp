#include "ScopingBlock.hpp"

#include "Utils.hpp"
namespace SDIM
{
	bool ScopingBlock::AddVariable(const std::string& var_name, const Variable& var)
	{
		const auto& it = variables_.find(var_name);
		if (it == variables_.end())
		{
			// var doesn't exist success
			variables_.emplace((std::string)var_name, (Variable)var);
			return true;
		}
		return false;
	}
	Variable ScopingBlock::GetVariable(const std::string& var_name)
	{
		const auto& it = variables_.find(var_name);
		if (it == variables_.end())
		{
			// var doesn't exist failure

			return Variable();
		}
		return it->second;
	}
	void ScopingBlock::PrintScope() const
	{
		Utils::Log("Scoping block ", scope_name_, " Contains ", variables_.size(), " variables");

		for (const auto& it : variables_)
		{
			Utils::Log("Variable ", it.first, " with current value ", it.second.ToString());
		}
	}
	std::string ScopingBlock::GetName() const
	{
		return scope_name_;
	}
}