#pragma once
#include <map>

class DataHeap {
public:
	std::map<std::string, int> labels;
	std::map<std::string, int> data;
	std::map<std::string, int> code_data;
	std::map<std::string, std::string> data_size;
	std::map< std::string, int> macros;
};