#pragma once
#include "DataHeap.h"
#include "Offset.h"


class ByteCode {
public:

	Offset* offset; 

	ByteCode(Offset* _offset) {
		offset = _offset;
	}

	void second_through(); 
};