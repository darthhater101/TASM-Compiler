#pragma once
#include <vector>
#include "Lexical.h"
#include "Data.h"

class Syntaxer { 
public:

	Lexical* dmp;

	std::vector<synDump> synline;

	Syntaxer(Lexical* _dmps) { 
		dmp = _dmps;
	}

	void start();
	void print();
};