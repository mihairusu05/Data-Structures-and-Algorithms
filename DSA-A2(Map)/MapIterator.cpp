#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->currentNode = d.head; // Initialize the iterator to the head of the map
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

void MapIterator::first() {
	this->currentNode = map.head; // Set the iterator to the first element of the map
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

void MapIterator::next() {
	if (!this->valid()) {
		throw exception(); // If the iterator is not valid, throw an exception
	}
	currentNode = currentNode->next; // Move to the next element
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

TElem MapIterator::getCurrent() {
	if (!this->valid()) {
		throw exception();
	}
	return this->currentNode->data; // Return the current element
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

bool MapIterator::valid() const {
	return this->currentNode != nullptr; // Check if the current element is valid
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)

void MapIterator::last() {
	this->currentNode = map.tail; // Set the iterator to the last element of the map
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)


void MapIterator::previous() {
	if (!this->valid()) {
		throw exception();
	}
	this->currentNode = this->currentNode->prev; // Move to the previous element
}
// Complexity:
// Worst Case: theta(1)
// Average Case: theta(1)
// Best Case: theta(1)