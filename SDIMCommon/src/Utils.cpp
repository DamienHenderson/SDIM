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
#else
			// avoid generating warnings
			(void)disasm;
#endif
		}

		UInt8 InstructionToUInt8(Instruction instruction)
		{
			return static_cast<UInt8>(instruction);
		}

		UInt16 UInt16ToLittleEndian(UInt16 value)
		{
			
			if (IsLittleEndian())
			{
				return value;
			}
			// TODO: use intrinsics for this
			UInt16 low_byte = value & 0xFF;
			UInt16 high_byte = (value >> 8) & 0xFF;
			return low_byte << 8 | high_byte;
		}

		UInt32 UInt32ToLittleEndian(UInt32 value)
		{
			if (IsLittleEndian())
			{
				return value;
			}
			// TODO: use intrinsics for this
			UInt32 byte_0 = value & 0xFF;
			UInt32 byte_1 = (value >> 8) & 0xFF;
			UInt32 byte_2 = (value >> 16) & 0xFF;
			UInt32 byte_3 = (value >> 24) & 0xFF;
			return byte_0 << 24 | byte_1 << 16 | byte_2 << 8 | byte_3;
		}

		UInt64 UInt64ToLittleEndian(UInt64 value)
		{
			if (IsLittleEndian())
			{
				return value;
			}
			// TODO: use intrinsics for this
			UInt64 byte_0 = value & 0xFF;
			UInt64 byte_1 = (value >> 8) & 0xFF;
			UInt64 byte_2 = (value >> 16) & 0xFF;
			UInt64 byte_3 = (value >> 24) & 0xFF;
			UInt64 byte_4 = (value >> 32) & 0xFF;
			UInt64 byte_5 = (value >> 40) & 0xFF;
			UInt64 byte_6 = (value >> 48) & 0xFF;
			UInt64 byte_7 = (value >> 56) & 0xFF;
			return (byte_0 << 56) | (byte_1 << 48) | (byte_2 << 40) | (byte_3 << 32) | (byte_4 << 24) | (byte_5 << 16) | (byte_6 << 8) | byte_7;
		}


		
	}
}