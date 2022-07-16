#pragma once

#include "HashNode.h"
#include "KeyHash.h"
#include <cstddef>


// Hash map class template
template <typename K, typename V, size_t tableSize, typename F = KeyHash<K, tableSize> >
class HashMap
{
private:
	std::recursive_mutex printNodeMutex;

public:
	HashMap() :
		table(),
		hashFunc()
	{
	}

	~HashMap()
	{
		// destroy all buckets one by one
		for (size_t i = 0; i < tableSize; ++i) {
			HashNode<K, V>* entry = table[i];
			while (entry != NULL) {
				HashNode<K, V>* prev = entry;
				entry = entry->getNext();
				delete prev;
			}

			table[i] = NULL;
		}
	}

	bool get(const K& key, V& value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* entry = table[hashValue];

		while (entry != NULL) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return true;
			}

			entry = entry->getNext();
		}

		return false;
	}

	void put(const K& key, const V& value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new HashNode<K, V>(key, value);

			if (prev == NULL) {
				// insert as first bucket
				table[hashValue] = entry;

			}
			else {
				prev->setNext(entry);
			}

		}
		else {
			// just update the value
			entry->setValue(value);
		}
	}

	void remove(const K& key)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			// key not found
			return;

		}
		else {
			if (prev == NULL) {
				// remove first bucket of the list
				table[hashValue] = entry->getNext();

			}
			else {
				prev->setNext(entry->getNext());
			}

			delete entry;
		}
	}

	void removeAllKey(const K& key) {
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = table[hashValue];

		while (table[hashValue] != NULL)
		{
			hashValue = hashFunc(key);
			prev = NULL;
			entry = table[hashValue];
			while (entry != NULL && entry->getKey() != key) {
				prev = entry;
				entry = entry->getNext();
			}

			if (entry == NULL) {
				if (prev != NULL) {
					table[hashValue] = entry;
					delete prev;
					return;
				}
				else {
					return;
				}
			}
			else {
				if (prev == NULL) {
					// remove first bucket of the list
					table[hashValue] = entry->getNext();

				}
				else {
					prev->setNext(entry->getNext());
				}

				delete entry;
			}
		}
	}

	void printHashTable() {
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = NULL;
		K key;
		V val;
		bool res;
		unsigned long hashValue = NULL;

		//print hash map
		for (int i = 0; i < tableSize; i++)
		{
			entry = table[i];

			while (entry != NULL)
			{
				prev = entry;
				entry = entry->getNext();

				key = prev->getKey();
				val = prev->getValue();

				res = get(key, val);
				std::cout << "Element [" << i << "]: " << std::endl;
				if (res)
					assert(std::cout << "Key: " << key << std::endl << "Val: " << val << std::endl);
				std::cout << std::endl;
			}

			prev = NULL;
			entry = NULL;
		}
	}

	void safe_printHashTable() {
		HashNode<K, V>* prev = NULL;
		HashNode<K, V>* entry = NULL;
		K key;
		V val;
		bool res;
		{
			std::lock_guard<std::recursive_mutex> guardMe(printNodeMutex);
			unsigned long hashValue = NULL;
		}
		//print hash map
		for (int i = 0; i < tableSize; i++)
		{
			{
				std::lock_guard<std::recursive_mutex> guardMe(printNodeMutex);
				entry = table[i];

				while (entry != NULL)
				{
					prev = entry;
					entry = entry->getNext();

					key = prev->getKey();
					val = prev->getValue();

					res = get(key, val);
					std::cout << "Element [" << i << "]: " << std::endl;
					if (res)
						assert(std::cout << "Key: " << key << std::endl << "Val: " << val << std::endl);
					std::cout << std::endl;
				}

				prev = NULL;
				entry = NULL;
			}
		}
	}
	size_t size() {
		return tableSize;
	}

private:
	HashMap(const HashMap& other);
	const HashMap& operator=(const HashMap& other);
	// hash table
	HashNode<K, V>* table[tableSize];
	F hashFunc;
};
