#include "ILCompiler.hpp"

#include "LangUtils.hpp"

namespace SDIM
{
	ILCompiler::ILCompiler()
	{
	}


	ILCompiler::~ILCompiler()
	{
	}
	std::vector<UInt8> ILCompiler::CompileString(const std::string& program_string)
	{
		std::vector<UInt8> program_data;
		return program_data;
	}
	std::vector<UInt8> ILCompiler::CompileFile(const std::string& file_path)
	{
		std::string file_contents = SDIM::ReadWholeFile(file_path);

		return CompileString(file_contents);
	}
}
