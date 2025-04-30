#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	elems = new TElem[10];
	positions = new int[10];
	capacityElems = 10;
	capacityPos = 10;
	sizeElems = 0;
	sizePos = 0;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

void Bag::add(TElem elem) {
	/// Check if elem exists
	int elemIndex = -1;
	for (int i = 0; i < sizeElems; i++) {
		if (elems[i] == elem) {
			elemIndex = i;
			break;
		}
	}

	/// Add to elems if first occurence
	if (elemIndex == -1) {
		if (sizeElems == capacityElems) {
			capacityElems *= 2;
			TElem* newElems = new TElem[capacityElems];
			for (int i = 0; i < sizeElems; i++) {
				newElems[i] = elems[i];
			}
			delete[] elems;
			elems = newElems;
		}
		elems[sizeElems] = elem;
		elemIndex = sizeElems;
		sizeElems++;
	}

	/// Add to positions
	if (sizePos == capacityPos) {
		capacityPos *= 2;
		int* newPositions = new int[capacityPos];
		for (int i = 0; i < sizePos; i++) {
			newPositions[i] = positions[i];
		}
		delete[] positions;
		positions = newPositions;
	}

	positions[sizePos] = elemIndex;
	sizePos++;
}
/// WC: O(n), AG: O(n), BC: theta(1)

bool Bag::remove(TElem elem) {
	/// Checks for the elem in the Bag
	int elemIndex = -1;
	for (int i = 0; i < sizeElems; i++) {
		if (elems[i] == elem) {
			elemIndex = i;
			break;
		}
	}

	/// Returns false if not found
	if (elemIndex == -1) {
		return false;
	}

	/// Deletes an instance from positions
	for (int i = 0; i < sizePos; i++) {
		if (positions[i] == elemIndex) {
			positions[i] = positions[sizePos - 1];
			sizePos--;
			break;
		}
	}

	/// Check if element still in positions
	bool stillExists = false;
	for (int i = 0; i < sizePos; i++) {
		if (positions[i] == elemIndex) {
			stillExists = true;
			break;
		}
	}

	/// If no more ,remove from elems
	if (!stillExists) {
		elems[elemIndex] = elems[sizeElems - 1];
		sizeElems--;

		for (int i = 0; i < sizePos; i++) {
			if (positions[i] == sizeElems) {
				positions[i] = elemIndex;
			}
		}
	}

	return true;
}
/// WC: O(n), AG: O(n), BC: O(1)

bool Bag::search(TElem elem) const {
	
	for (int i = 0; i < sizeElems; i++) {
		if (elems[i] == elem)
			return true;
	}
	return false;
}
// WC: theta(n), AG: O(n), BC: theta(1)

int Bag::nrOccurrences(TElem elem) const {
	/// Find elem index
	int elemIndex = -1;
	for (int i = 0; i < sizeElems; i++) {
		if (elems[i] == elem) {
			elemIndex = i;
			break;
		}
	}

	/// If elem not found
	if (elemIndex == -1) {
		return 0;
	}

	/// Count occurrences in positions
	int count = 0;
	for (int i = 0; i < sizePos; i++) {
		if (positions[i] == elemIndex) {
			count++;
		}
	}

	return count;
}
/// WC: theta(n), AG: O(n), BC: theta(1)

int Bag::size() const {
	
	return sizePos;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

bool Bag::isEmpty() const {

	return sizePos == 0;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

BagIterator Bag::iterator()  {
	
	return BagIterator(*this);
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

Bag::~Bag() {
	
	delete[] elems;
	delete[] positions;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)
