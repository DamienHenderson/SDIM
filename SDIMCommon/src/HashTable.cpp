#include "HashTable.hpp"

#include "Utils.hpp"

#include <cstdlib>

namespace SDIM
{
	HashTable::HashTable()
	{
	}
	HashTable::~HashTable()
	{
		if (strings_ != nullptr)
		{
			delete[] strings_;
			strings_ = nullptr;
		}
	}
	bool HashTable::Exists(const char* string)
	{
		if (strings_ == nullptr)
		{
			return false;
		}
		UInt64 hash = SDIM::Utils::FNV1AHash(string, std::strlen(string));
		UInt64 idx = hash % capacity_;
		// This won't work with hash collisions
		return strings_[idx] != nullptr;
	}
	void HashTable::Resize(size_t count)
	{
		if (capacity_ == count)
		{
			// already the requested size 
			return;
		}
		char** strings = new char* [count]();
		// copy elements
		if (capacity_ > count)
		{
			// Hash Table is being shrunk so some elements may be lost
#ifdef SDIM_VERBOSE
			SDIM::Utils::Log("[Warning] Hash Table with size(", capacity_, ") being shrunk to ", count, " elements");
#endif
			std::memcpy(strings, strings_, count * sizeof(strings));
		}
		else
		{
			std::memcpy(strings, strings_, capacity_ * sizeof(strings));
		}
		
		// get rid of old strings and redirect pointer to new array
		delete[] strings_;
		strings_ = strings;
		capacity_ = count;
	}
	void HashTable::AddString(const char* string)
	{
		if (strings_ == nullptr)
		{
			return;
		}
		static_assert(sizeof(size_t) == sizeof(UInt64), "size_t is not the same size as UInt64");
		UInt64 hash = SDIM::Utils::FNV1AHash(string, std::strlen(string));
		UInt64 idx = hash % capacity_;
		
		if (strings_[idx] != nullptr)
		{
			// hash collision or the string already exists
			// if the second is true everything is fine
			// if the first is true then i need to handle it 
			// for now just skip
			return;
		}
		char* str = new char[std::strlen(string)];
		std::memcpy(str, string, std::strlen(string));
		strings_[idx] = str;
	}
	const char* HashTable::GetString(const char* string)
	{
		if (strings_ == nullptr)
		{
			return nullptr;
		}
		UInt64 hash = SDIM::Utils::FNV1AHash(string, std::strlen(string));
		UInt64 idx = hash % capacity_;
		
		return strings_[idx];
	}
	void HashTable::RemoveString(const char* string)
	{
		if (strings_ == nullptr)
		{
			return;
		}
		UInt64 hash = SDIM::Utils::FNV1AHash(string, std::strlen(string));
		UInt64 idx = hash % capacity_;

		if (strings_[idx] == nullptr)
		{
			return;
		}
		delete[] strings_[idx];
		strings_[idx] = nullptr;
	

	}
}
