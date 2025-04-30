#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->first();
}
/// All cases : theta(1)
void SMMIterator::first(){
	this->currentKeyIndex = map.keyHead;
	if (this->currentKeyIndex != -1) {
		this->currentValueIndex = map.keyValueHead[currentKeyIndex];

	}
	else {
		this->currentValueIndex = -1;
	}
}
/// All cases : theta(1)

void SMMIterator::next(){
	if (!this->valid()) {
		throw exception();
	}
	this->currentValueIndex = map.valueNext[currentValueIndex];

	while (this->currentValueIndex == -1 && this->currentKeyIndex != -1) {
		this->currentKeyIndex = map.keyNext[this->currentKeyIndex];
		if (this->currentKeyIndex != -1) {
			this->currentValueIndex = map.keyValueHead[this->currentKeyIndex];
		}
	}
}
/// Best Case : theta(1), Worst Case : O(n), Average Case : theta(1) assuming that usually it will find a valid key value pair 

bool SMMIterator::valid() const{
	return this->currentKeyIndex != -1 && this->currentValueIndex != -1;
}
/// All cases : theta(1)

TElem SMMIterator::getCurrent() const{
	if (!this->valid()) {
		throw exception();
	}
	return make_pair(map.keys[currentKeyIndex], map.values[currentValueIndex]);
}
///	All cases : theta(1)


