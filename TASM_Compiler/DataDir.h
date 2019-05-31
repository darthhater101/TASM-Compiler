#pragma once
#include "Syntaxer.h"
#include "Data.h"

typedef enum {
	DB,
	DW,
	DD
} DATASIZE;

class DataDir {
public:
	DataDir(synDump synline);
	int calculateOffset();
	std::string byteCode();
	std::string stringHandle();

	std::string name;
	DATASIZE size;
	std::string _value;
	TYPE value_type;
};