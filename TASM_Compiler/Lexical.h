#pragma once
#include "Data.h"
#include "AsmHelper.h"
#include <iostream>



class Lexical { 
public:

	std::string filename; 
	std::vector<dump> dmps; 

	Lexical(std::string name) { filename = name; }

	void start(); 

	std::vector<lexem> parse(std::string line); 

	TYPE lexem_type(std::string &word);

	void print();
};