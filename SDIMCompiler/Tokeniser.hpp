#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cassert>
namespace SDIM
{


	class Tokeniser
	{
	public:
		Tokeniser();
		~Tokeniser();

		void ParseFile(const std::string& file_path);
	};

}