#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

Map::~Map() {
	///Deletes all the nodes in the list
	DLLNode* current = this->head;
	while (current != nullptr) {
		DLLNode* next = current->next;
		delete current;
		current = next;
	}
}
// Complexity:
// Worst Case: theta(n)
// Average Case: theta(n)
// Best Case: theta(n)

TValue Map::add(TKey c, TValue v) {
	///Checks for the existence of the key in the list
	DLLNode* current = head;
	while (current != nullptr) {
		if (current->data.first == c) {
			TValue oldValue = current->data.second;
			current->data.second = v;
			return oldValue;
		}
		current = current->next;
	}

	///If the key does not exist, create a new node
	///and add it to the end of the list
	DLLNode* newNode = new DLLNode(TElem(c, v), this->tail, nullptr);
	if (this->tail != nullptr) {
		this->tail->next = newNode;
	}
	else {
		this->head = newNode;
	}
	this->tail = newNode;
	this->length++;
	return NULL_TVALUE;
}
// Complexity:
// Worst Case: O(n)
// Average Case: O(n)
// Best Case: O(1)

TValue Map::search(TKey c) const {
	DLLNode* current = head;
	while (current != nullptr) {
		if (current->data.first == c) {
			return current->data.second;
		}
		current = current->next;
	}
	return NULL_TVALUE;
}
// Complexity:
// Worst Case: O(n)
// Average Case: O(n)
// Best Case: O(1)

TValue Map::remove(TKey c) {
	DLLNode* current = head;
	while (current != nullptr) {
		if (current->data.first == c) {
			TValue val = current->data.second;

			// Link the previous and next nodes	based on the current node's position 
			// If cuurent is head, tail, or in the middle

			if (current->prev != nullptr)
				current->prev->next = current->next;
			else
				head = current->next;

			if (current->next != nullptr)
				current->next->prev = current->prev;
			else
				tail = current->prev;

			delete current;
			length--;
			return val;
		}
		current = current->next;
	}
	return NULL_TVALUE;
}
// Complexity:
// Worst Case: O(n)
// Average Case: O(n)
// Best Case: teht(1)

int Map::size() const {
	return this->length;
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

bool Map::isEmpty() const {
	return this->length == 0;
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)
