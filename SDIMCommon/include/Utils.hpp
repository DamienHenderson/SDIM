#pragma once

#include "Types.hpp"

#include <string>
#include <iostream>
#include <sstream>

namespace SDIM
{
	// TODO: move utils to shared SDIM common library and combine with general compiler utils
	namespace Utils
	{
		// This shouldn't be constexpr because the entire point is querying at runtime 
		// If it was constexpr the querying would be at compile time and would be totally useless because 
		// it would refer to the endianness of the machine compiling it
		bool IsLittleEndian();

		void TerminateLog();

		template <typename T>
		void Log(T&& arg);

		template<typename T>
		void LogIntermediate(T && arg);
		
		template <typename T, typename... Args>
		void Log(T&& arg, Args&&... args);

		
		template<typename T>
		void Log(T && arg)
		{
			std::cout << arg << "\n";
		}

		template<typename T>
		void LogIntermediate(T && arg)
		{
			std::cout << arg;
		}
		// Variadic Log Function
		// Allows any number of variables to be logged in a single call
		template<typename T, typename ...Args>
		void Log(T && arg, Args && ...args)
		{
			LogIntermediate(arg);
			Log(args...);
			if constexpr (sizeof...(args) == 0)
			{
				TerminateLog();
			}
		}

		

		
		/// TODO: variadic ConstructString function to go alongside the Log functions
		template <typename T>
		std::string ConstructString(T&& arg);

		template <typename T, typename... Args>
		std::string ConstructString(T&& arg, Args&&... args);

		template<typename T>
		std::string ConstructString(T && arg)
		{
			// definitely not optimal but it can be improved later
			std::stringstream ss;
			ss << arg;
			return ss.str();
		}

		template<typename T, typename ...Args>
		std::string ConstructString(T && arg, Args && ...args)
		{
			std::string base = ConstructString(arg);
			
			if constexpr(sizeof...(args) == 0)
			{
				return base;
			}
			else
			{
				return base + ConstructString(args...);
			}
		}

		

		void Disassemble(const std::string& disasm);

		UInt8 InstructionToUInt8(Instruction instruction);

		/// Converts integers to Little Endian to allow them to be written directly to disk
		/// If the platform is Little Endian then nothing is done to the value
		UInt16 UInt16ToLittleEndian(UInt16 value);

		UInt32 UInt32ToLittleEndian(UInt32 value);
		
		UInt64 UInt64ToLittleEndian(UInt64 value);

		// Implementation of the new C++20 std::bit_cast but made to work on C++17 and possibly earlier versions
		template <typename To, typename From>
		const To ByteCast(const From& value);
		
		template<typename To, typename From>
		const To ByteCast(const From& src)
		{
			static_assert(sizeof(To) == sizeof(From) && std::is_trivially_copyable<From>::value && std::is_trivial<To>::value, "ByteCast must be called with 2 types of the same with the From type trivially copyable and the To type trivially constructible");
			To dest;
			std::memcpy(&dest, &src, sizeof(src));
			return dest;
		}

		/// Returns the FNV1a Hash of a string
		/// Note that this hash is not cryptographically secure so it should net be used for that purpose
		UInt64 FNV1AHash(const char* str, size_t length);

	}
}