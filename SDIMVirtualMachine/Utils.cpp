#include "Utils.hpp"

#include <iostream>

namespace SDIM
{
	namespace Utils
	{
		bool IsLittleEndian()
		{
			union
			{
				char c[4];
				UInt32 ui;
			} end_test = {0x01020304};

			return end_test.c[0] == 0x04;
		}
		void LogString(const std::string & log_str)
		{
			std::cout << log_str << "\n";
		}
	}
}