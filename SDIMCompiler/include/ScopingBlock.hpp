#pragma once

#include "Types.hpp"

#include <unordered_map>
#include <string>
namespace SDIM
{
	// Scoping block
	// has it's own set of key value pairs of strings to variables
	// each scoping block is completely self contained
	// variables in scopes closer to the current scoping block have precedence over variables in higher scopes (for example variables in function scope have precedence over variables in global scope)
	class ScopingBlock
	{
	public:
		ScopingBlock(const std::string& scope_name) : scope_name_(scope_name) {}
		~ScopingBlock() {}
		/// returns true if the variable was successfully added 
		/// returns false if the variable was not added
		bool AddVariable(const std::string& var_name, const Variable& var);

		/// Returns the current value of a variable 
		/// If the variable doesn't exist the variable will have it's type set to unknown
		Variable GetVariable(const std::string& var_name);

		void PrintScope() const;

		std::string GetName() const;

	private:
		std::unordered_map<std::string, Variable> variables_;

		std::string scope_name_;
	};
}