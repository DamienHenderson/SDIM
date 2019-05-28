#pragma once

#include <Utils.hpp>
#include <Types.hpp>

#include "BytecodeGenerator.hpp"

namespace SDIM
{
	class IRCompiler
	{
	public:
		IRCompiler();
		~IRCompiler();
	private:
		BytecodeGenerator generator_;
	};

}

