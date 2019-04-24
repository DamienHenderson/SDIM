#pragma once

namespace SDIM
{
	/// HashTAble class for interning strings
	/// This will allow string compares to only use raw pointer equality
	/// Will be useful for constant strings
	class HashTable
	{
	public:
		HashTable();
		~HashTable();
		/// Is the string already in the hash table
		bool Exists(const char* string);
		/// Resize the hash table
		void Resize(size_t count);
		/// Add a string to the hash table
		/// if the string already exists then nothing will happen 
		void AddString(const char* string);
		/// Get the address of the interned string equivalent to the string passed in
		const char* GetString(const char* string);

	private:
		char** strings_{ nullptr };
		size_t capacity_{ 0 };
	};
}