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
		(void)string;
		return false;
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
		static_assert(sizeof(size_t) == sizeof(UInt64), "size_t is not the same size as UInt64");
		UInt64 hash = SDIM::Utils::FNV1AHash(string, std::strlen(string));
		UInt64 idx = hash % capacity_;
		(void)idx;

	}
	const char* HashTable::GetString(const char* string)
	{
		UInt64 hash = SDIM::Utils::FNV1AHash(string, std::strlen(string));
		UInt64 idx = hash % capacity_;
		(void)idx;
		return nullptr;
	}
}