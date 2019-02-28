#pragma once

#include <string>
#include <vector>

#include "Token.hpp"
namespace SDIM
{


	class Scanner
	{
	public:
		Scanner();
		~Scanner();

		/// Scans through a source code file and splits it out into tokens
		/// tokens should be a vector with user ownership which will be written into, noting that any
		/// existing data in tokens will be preserved
		bool ScanFile(const std::string& path, std::vector<Token>& tokens);

		

	};

}