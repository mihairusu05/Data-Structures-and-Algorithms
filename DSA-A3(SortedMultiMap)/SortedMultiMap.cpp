#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r;
	this->keyCapacity = INITIAL_KEY_CAPACITY;
	this->valueCapacity = INITIAL_VALUE_CAPACITY;
	
	this->keys = new TKey[this->keyCapacity];
	this->keyNext = new int[this->keyCapacity];
	this->keyValueHead = new int[this->keyCapacity];
	this->keyHead = -1;

	for (int i = 0; i < this->keyCapacity; i++) {
		this->keyNext[i] = i + 1;
	}

	this->keyNext[this->keyCapacity - 1] = -1;
	this->keyFirstFree = 0;

	this->values = new TValue[this->valueCapacity];
	this->valueNext = new int[this->valueCapacity];

	for (int i = 0; i < this->valueCapacity; i++) {
		this->valueNext[i] = i + 1;
	}
	this->valueNext[this->valueCapacity - 1] = -1;
	this->valueFirstFree = 0;

	this->totalSize = 0;

}
/// Best/Worst/Average Case : O(capacity(key + value))

void SortedMultiMap::add(TKey c, TValue v) {
	int prev = -1;
	int current = this->keyHead;

	while (current != -1 && this->rel(keys[current], c)) {
		if (keys[current] == c)
			break;
		prev = current;
		current = this->keyNext[current];
	}

	if (current != -1 && keys[current] == c) {
		int valPos = this->allocateValue();
		this->values[valPos] = v;
		this->valueNext[valPos] = this->keyValueHead[current];
		this->keyValueHead[current] = valPos;
	}

	else {
		int keyPos = this->allocateKey();
		this->keys[keyPos] = c;

		int valPos = this->allocateValue();
		this->values[valPos] = v;
		this->valueNext[valPos] = -1;
		this->keyValueHead[keyPos] = valPos;

		if (prev == -1) {
			this->keyNext[keyPos] = keyHead;
			this->keyHead = keyPos;
		}
		else {
			this->keyNext[keyPos] = this->keyNext[prev];
			this->keyNext[prev] = keyPos;
		}
	}

	this->totalSize++;
}
/// Best Case : theta(1), Worst Case : theta(n),  Average Case : O(n)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> result;
	int current = this->keyHead;

	while (current != -1 && this->rel(this->keys[current], c)) {
		if (this->keys[current] == c) {
			int val = this->keyValueHead[current];
			while (val != -1) {
				result.push_back(values[val]);
				val = this->valueNext[val];
			}
			break;
		}
		current = this->keyNext[current];
	}
	return result;
	
}
/// Best Case : theta(1), Worst Case : O(n + m) n is nr of keys , m is nr of values,  Average Case : theta(n + m) --||-- 

bool SortedMultiMap::remove(TKey c, TValue v) {
	int prevKey = -1;
	int currentKey = this->keyHead;

	while (currentKey != -1 && this->rel(this->keys[currentKey], c)) {
		if (this->keys[currentKey] == c) {
			break;

		}
		prevKey = currentKey;
		currentKey = this->keyNext[currentKey];

	}

	if (currentKey == -1 || keys[currentKey] != c)
		return false;

	int currentVal = this->keyValueHead[currentKey];
	int prevVal = -1;
	
	while (currentVal != -1 && this->values[currentVal] != v) {
		prevVal = currentVal;
		currentVal = this->valueNext[currentVal];
	}

	if (currentVal == -1) {
		return false;
	}

	if (prevVal == -1) {
		this->keyValueHead[currentKey] = this->valueNext[currentVal];
	}
	else {
		this->valueNext[prevVal] = this->valueNext[currentVal];
	}
    
	this->deallocateValue(currentVal);
	totalSize--;

	if (keyValueHead[currentKey] == -1) {
		if (prevKey == -1) {
			keyHead = keyNext[currentKey];
		}
		else {
			keyNext[prevKey] = keyNext[currentKey];
		}
		deallocateKey(currentKey);
	}

	return true;
}
/// Best Case : theta(1), Worst Case : O(n + m) n is nr of keys , m is nr of values,  Average Case : theta(n + m) --||--

int SortedMultiMap::size() const {
	
	return this->totalSize;
}
/// All cases : theta(1)

bool SortedMultiMap::isEmpty() const {
	return this->totalSize == 0;
}
/// All cases : theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
/// All cases : theta(1)

SortedMultiMap::~SortedMultiMap() {
	delete[] this->keys;
	delete[] this->keyNext;
	delete[] this->keyValueHead;

	delete[] this->values;
	delete[] this->valueNext;
}
/// All cases : theta(1)


vector<TValue> SortedMultiMap::removeKey(TKey c) {
	vector<TValue> result;
	int prevKey = -1;
	int currentKey = this->keyHead;

	while (currentKey != -1 && this->rel(this->keys[currentKey], c)) {
		if (this->keys[currentKey] == c) {
			break;
		}
		prevKey = currentKey;
		currentKey = this->keyNext[currentKey];
	}
	
	if (currentKey == -1 || this->keys[currentKey] != c)
		return result;
	
	int currentVal = this->keyValueHead[currentKey];
	while (currentVal != -1) {
		result.push_back(this->values[currentVal]);
		int nextVal = this->valueNext[currentVal];
		this->deallocateValue(currentVal);  
		this->totalSize--;
		currentVal = nextVal;
	}
	
	if (prevKey == -1) {
		this->keyHead = this->keyNext[currentKey];
	}
	else {
		this->keyNext[prevKey] = this->keyNext[currentKey];
	}

	this->deallocateKey(currentKey);  

	return result;
}

/// Best Case : theta(1), Worst Case : O(n + m) n is nr of keys , m is nr of values,  Average Case : theta(n + m) --||--