#pragma once

#include "Types.hpp"

#include <string>

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
			if (sizeof...(args) == 0)
			{
				TerminateLog();
			}
		}

		


	}
}