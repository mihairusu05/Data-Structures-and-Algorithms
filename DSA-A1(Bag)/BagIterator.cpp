#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

BagIterator::BagIterator(Bag& c) : bag(c)
{
	currentIndex = 0;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

void BagIterator::first() {
	currentIndex = 0;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

void BagIterator::next() {
	if (!valid()) {
		throw exception();
	}
	currentIndex++;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

bool BagIterator::valid() const {
	return currentIndex < bag.sizePos;
}
/// WC: theta(1), AG: theta(1), BC: theta(1)

TElem BagIterator::getCurrent() const {
	if (!valid()) {
		throw exception();
	}
	/// Iterator is over the positions array, not over the elems array
	int pos = bag.positions[currentIndex];
	return bag.elems[pos];
}
/// WC: theta(1), AG: theta(1), BC: theta(1)


TElem BagIterator::remove() {
    
    if (!valid()) {
        throw exception();
    }

    int currentPos = bag.positions[currentIndex];
    TElem removedElem = bag.elems[currentPos];

    bag.positions[currentIndex] = bag.positions[bag.sizePos - 1];
    bag.sizePos--;

    bool stillExists = false;
    for (int i = 0; i < bag.sizePos; i++) {
        if (bag.positions[i] == currentPos) {
            stillExists = true;
            break;
        }
    }

    if (!stillExists) {
        bag.elems[currentPos] = bag.elems[bag.sizeElems - 1]; 
        bag.sizeElems--;

        for (int i = 0; i < bag.sizePos; i++) {
            if (bag.positions[i] == bag.sizeElems) {
                bag.positions[i] = currentPos;
            }
        }
    }

    if (currentIndex >= bag.sizePos) {
        currentIndex = bag.sizePos;
    }

    return removedElem; // Return the removed element
}
/// WC: O(n), AG: O(n), BC: O(1)

