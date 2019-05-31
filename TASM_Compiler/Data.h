#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
 

enum TYPE {
	USERS,
	REGISTER,
	DIRECTIVE,
	COMMAND,
	HEX,
	DEC,
	OCT,
	BIN,
	TEXT,
	OCHAR
};

typedef struct { 
	int id;
	std::string word;
	int size;
	TYPE type;

	void push(int _id, std::string _word, int _size, TYPE _type) {
		id = _id;
		word = _word;
		size = _size;
		type = _type;
	}

	void print() {
		std::cout << "ID: " << id << std::endl
			<< "LEXEM: " << word << std::endl
			<< "SIZE: " << size << std::endl
			<< "TYPE: " << type << std::endl;
	}

} lexem;

typedef struct {  
	std::vector<lexem> lxms;
	std::string str;
	int str_num;

	void push(std::vector<lexem> _lxms, std::string _str, int _str_num) {
		lxms = _lxms;
		str = _str;
		str_num = _str_num;
	}

	void print() {
		std::cout << "NUM: " << str_num << std::endl
			<< "STR: " << str << std::endl;
		for (auto x : lxms) {
			x.print();
		}
	}

} dump;

typedef struct { 

	int name_index = -1;
	int mnemo_index = -1;
	int mnemo_size = -1;

	int arg_index_1 = -1;
	int arg_size_1 = -1;
	int arg_index_2 = -1;
	int arg_size_2 = -1;

	dump dmp;

	void push(int name, int mnemoi, int mnemos, int argi1, int args1, int argi2, int args2, dump _dmp) {
		name_index = name;
		mnemo_index = mnemoi;
		mnemo_size = mnemos;
		arg_index_1 = argi1;
		arg_size_1 = args1;
		arg_index_2 = argi2;
		arg_size_2 = args2;
		dmp = _dmp;
	}

	void print() {
		dmp.print();
		std::cout << "Name = " << name_index << std::endl
			<< "Mnemo_index = " << mnemo_index << std::endl
			<< "Mnemo_size = " << mnemo_size << std::endl
			<< "Arg_index_1 = " << arg_index_1 << std::endl
			<< "Arg_size_1 = " << arg_size_1 << std::endl
			<< "Arg_index_2 = " << arg_index_2 << std::endl
			<< "Arg_size_2 = " << arg_size_2 << std::endl;
	}

} synDump;

typedef struct { 
	
	synDump sdmp;

	std::string offset;
	std::string modrm;

	void push(synDump _sdmp, std::string _offset) {
		sdmp = _sdmp;
		offset = _offset;
	}

	void print() {
		std::cout << std::left << std::setw(5) << sdmp.dmp.str_num << std::setw(10) << offset << std::left << std::setw(27) << modrm << "  " << sdmp.dmp.str << std::endl;
	}

} offsetLine;