#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;

	DLLNode* currentNode;
	

	MapIterator(const Map& m);

public:
	void first();
	void last();
	void next();
	void previous();
	TElem getCurrent();
	bool valid() const;
};


