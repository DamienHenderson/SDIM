#include "VMState.hpp"

#include "Utils.hpp"
namespace SDIM
{

	namespace Utils
	{
		UInt8 ReadUInt8Literal(VMState & state, size_t location)
		{
			UInt8 literal_value{ 0 };
			if ((location + sizeof(literal_value) - 1) > state.program_length_)
			{
				SDIM::Utils::Log("Attempt to read immediate value which would read past the end of the program data");
				return literal_value;
			}
			for (int i = 0; i < sizeof(literal_value); i++)
			{
				unsigned char read_byte = static_cast<unsigned char>(state.program_data_[location + i]);
				literal_value |= read_byte << (i * 8);
			}

			return literal_value;
		}

		UInt16 ReadUInt16Literal(VMState & state, size_t location)
		{
			UInt16 literal_value{ 0 };
			if ((location + sizeof(literal_value) - 1) > state.program_length_)
			{
				SDIM::Utils::Log("Attempt to read immediate value which would read past the end of the program data");
				return literal_value;
			}
			for (int i = 0; i < sizeof(literal_value); i++)
			{
				UInt8 read_byte = static_cast<unsigned char>(state.program_data_[location + i]);
				literal_value |= read_byte << (i * 8);
			}

			return literal_value;
		}
		
		UInt32 ReadUInt32Literal(VMState & state, size_t location)
		{
			UInt32 literal_value{ 0 };
			if ((location + sizeof(literal_value) - 1) > state.program_length_)
			{
				SDIM::Utils::Log("Attempt to read immediate value which would read past the end of the program data");
				return literal_value;
			}
			for (int i = 0; i < sizeof(literal_value); i++)
			{
				unsigned char read_byte = static_cast<unsigned char>(state.program_data_[location + i]);
				literal_value |= read_byte << (i * 8);
			}

			return literal_value;
		}

		UInt64 ReadUInt64Literal(VMState & state, size_t location)

		{
			UInt64 literal_value{ 0 };
			if ((location + sizeof(literal_value) - 1) > state.program_length_)
			{
				SDIM::Utils::Log("Attempt to read immediate value which would read past the end of the program data");
				return literal_value;
			}
			for (int i = 0; i < sizeof(literal_value); i++)
			{
				unsigned char read_byte = static_cast<unsigned char>(state.program_data_[location + i]);
				literal_value |= read_byte << (i * 8);
			}

			return literal_value;
		}

		Int8 ReadInt8Literal(VMState & state, size_t location)
		{
			return static_cast<Int8>(ReadUInt8Literal(state, location));
		}

		Int16 ReadInt16Literal(VMState & state, size_t location)
		{
			return static_cast<Int16>(ReadUInt16Literal(state, location));
		}

		Int32 ReadInt32Literal(VMState & state, size_t location)
		{
			return static_cast<Int32>(ReadUInt32Literal(state, location));
		}

		Int64 ReadInt64Literal(VMState & state, size_t location)
		{
			return static_cast<Int64>(ReadUInt64Literal(state, location));
		}
		
	}
}