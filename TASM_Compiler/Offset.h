#pragma once
#include "Syntaxer.h"
#include "AsmHelper.h"
#include "DataDir.h"
#include "Commands.h"
#include "DataHeap.h"

class Offset { 

public:

	Syntaxer* sline; 
	std::vector<offsetLine> oline; 
	DataHeap dataheap;

	Offset(Syntaxer* _sline) {
		sline = _sline;
	}

	void first_through();


	void print(); 
};