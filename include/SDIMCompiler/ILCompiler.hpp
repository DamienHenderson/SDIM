#pragma once

#include <Utils.hpp>
#include <Types.hpp>

#include "BytecodeGenerator.hpp"

namespace SDIM
{
	class ILCompiler
	{
	public:
		ILCompiler();
		~ILCompiler();

		std::vector<UInt8> CompileString(const std::string& program_string);

		std::vector<UInt8> CompileFile(const std::string& file_path);
	private:
		BytecodeGenerator generator_;
	};

}

