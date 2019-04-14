#include "Utils.hpp"



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
			} end_test;
			end_test.ui = { 0x01020304 };
			return end_test.c[0] == 0x04;
		}

		void TerminateLog()
		{
			std::cout << "\n";
		}

		void Disassemble(const std::string & disasm)
		{
#ifdef SDIMVM_DEBUG
			Log(disasm);
#endif
		}


		
	}
}