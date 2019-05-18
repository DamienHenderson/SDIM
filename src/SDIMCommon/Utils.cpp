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
#ifdef SDIM_VERBOSE

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

		UInt64 FNV1AHash(const char* str, size_t length)
		{
			if (str == nullptr)
			{
				return ~(UInt64)0;
			}
			/// Values for 64 bit FNV1A
			constexpr UInt64 fnv_prime = 1099511628211u;
			constexpr UInt64 fnv_offset_basis = 14695981039346656037u;

			UInt64 hash = fnv_offset_basis;
			for (size_t i = 0; i < length; i++)
			{
				UInt64 next_byte = static_cast<UInt64>(str[i]);
				hash ^= next_byte;
				hash *= fnv_prime;
			}
			return hash;
		}

		UInt64 ReadUInt64Literal(const std::vector<char>& data, size_t idx)
		{
			UInt64 literal_value{ 0 };
			for (size_t i = 0; i < sizeof(literal_value); i++)
			{
				unsigned char read_byte = static_cast<unsigned char>(data[idx + i]);
				literal_value |= static_cast<UInt64>(read_byte) << (i * 8);
			}
			return literal_value;
		}


		
	}
}