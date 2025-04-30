#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(FixedCapBiMap& d) : map(d)
{
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::first() {
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::next() {
	if (this->currentPosition == this->map.mapSize)
		throw exception();

	this->currentPosition++;
}


TElem FixedCapBiMapIterator::getCurrent(){
	if (this->currentPosition == this->map.mapSize)
		throw exception();

	return this->map.elements[this->currentPosition];
}


bool FixedCapBiMapIterator::valid() const {
	
	return this->currentPosition < this->map.mapSize;
}

void FixedCapBiMapIterator::previous() {
	if (!this->valid()) {
		throw exception();
	}
	else
		if (this->currentPosition == 0)
			this->currentPosition = this->map.mapSize;
		else 
			this->currentPosition--;
}

//TElem FixedCapBiMapIterator::remove() {
//	if (!this->valid()) {
//		throw exception(); 
//	}
//
//	TElem removedElement = this->map.elements[this->currentPosition];
//
//	for (int i = this->currentPosition; i < this->map.mapSize - 1; i++) {
//		this->map.elements[i] = this->map.elements[i + 1];
//	}
//
//	this->map.mapSize--;
//
//	if (this->currentPosition == this->map.mapSize) {
//		this->currentPosition = this->map.mapSize; 
//	}
//
//	return removedElement;
//}



