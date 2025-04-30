#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:
        Relation rel;
		
		TKey* keys;
        int* keyNext;
        int* keyValueHead;
        int keyCapacity;
        int keyHead;
        int keyFirstFree;

		TValue* values;
		int* valueNext;
		int valueCapacity;
		int valueFirstFree;

		int totalSize;

		const int INITIAL_KEY_CAPACITY = 10;
		const int INITIAL_VALUE_CAPACITY = 20;

        void resizeKeys() {
            int newCapacity = this->keyCapacity * 2;

            TKey* newKeys = new TKey[newCapacity];
            int* newKeyNext = new int[newCapacity];
            int* newKeyValueHead = new int[newCapacity];

            for (int i = 0; i < this->keyCapacity; ++i) {
                newKeys[i] = this->keys[i];
                newKeyNext[i] = this->keyNext[i];
                newKeyValueHead[i] = this->keyValueHead[i];
            }

            for (int i = this->keyCapacity; i < newCapacity - 1; ++i) {
                newKeyNext[i] = i + 1;
            }
            newKeyNext[newCapacity - 1] = -1;

            delete[] this->keys;
            delete[] this->keyNext;
            delete[] this->keyValueHead;

            this->keys = newKeys;
            this->keyNext = newKeyNext;
            this->keyValueHead = newKeyValueHead;
            this->keyFirstFree = keyCapacity;
            this->keyCapacity = newCapacity;
        }
		/// All cases : O(capacity)

        void resizeValues() {
            int newCapacity = this->valueCapacity * 2;

            TValue* newValues = new TValue[newCapacity];
            int* newValueNext = new int[newCapacity];

            for (int i = 0; i < this->valueCapacity; ++i) {
                newValues[i] = this->values[i];
                newValueNext[i] = this->valueNext[i];
            }

            for (int i = this->valueCapacity; i < newCapacity - 1; ++i) {
                newValueNext[i] = i + 1;
            }
            newValueNext[newCapacity - 1] = -1;

            delete[] this->values;
            delete[] this->valueNext;

            this->values = newValues;
            this->valueNext = newValueNext;
            this->valueFirstFree = valueCapacity;
            this->valueCapacity = newCapacity;
        }
		/// All cases : O(capacity)

        int allocateKey() {
            if (this->keyFirstFree == -1) {
                this->resizeKeys();
            }
            int newPos = this->keyFirstFree;
            this->keyFirstFree = this->keyNext[keyFirstFree];
            return newPos;
        }
		/// Best Case : theta(1), Worst Case : O(capacity), Average Case : theta(1) (assuming resize not that often)

        void deallocateKey(int index) {
			this->keyNext[index] = this->keyFirstFree;
			this->keyValueHead[index] = -1;
			this->keyFirstFree = index;
        }
		/// All cases : theta(1)

        int allocateValue() {
			if (this->valueFirstFree == -1) {
				this->resizeValues();
			}
			int newPos = this->valueFirstFree;
			this->valueFirstFree = this->valueNext[valueFirstFree];
			return newPos;
        }
		/// Best Case : theta(1), Worst Case : O(capacity), Average Case : theta(1) (assuming resize not that often)

        void deallocateValue(int index) {
			this->valueNext[index] = this->valueFirstFree;
			this->valueFirstFree = index;
        }
		///All cases : theta(1)
    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	vector<TValue> removeKey(TKey c) ;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
