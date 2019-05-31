#pragma once
#include "AsmHelper.h"
#include "DataHeap.h"
#include "Syntaxer.h"
#include <regex>
#include <algorithm>

typedef enum { 
	REG,
	IMM,
	MEM
} OPERTYPE;

class Command { 
public:

	int occupied_bytes;
	std::string first;
	std::string second;
	DataHeap* dataheap;
	int offset;

	Command() {};

	virtual OPERTYPE operandType(std::string operand);
	virtual void recognizeOperands(synDump dump);
	virtual Command* canGet(std::string cmd);
	virtual void takeDataheap(DataHeap* _dataheap);
	virtual void takeOffset(std::string _offset);
	virtual int calculateOffset() = 0;
	virtual std::string defineBytecode() = 0;
};

class UnknownCmd : public Command {
public:
	UnknownCmd() {}
	virtual int calculateOffset() override { return 0; };
	virtual std::string defineBytecode() override { return std::string(); }
};

class Scasb : public Command {
public:
	Scasb() {
		occupied_bytes = 1;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Inc : public Command {
public:
	Inc(){
		occupied_bytes = 1;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Dec : public Command {
public:
	Dec(){
		occupied_bytes = 2;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Cmp : public Command {
public:
	Cmp() {
		occupied_bytes = 2;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Or : public Command {
public:
	Or(){
		occupied_bytes = 2;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class And : public Command {
public:
	And() {
		occupied_bytes = 2;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Add : public Command {
public:
	Add() {
		occupied_bytes = 2;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Mov : public Command {
public:
	Mov() {
		occupied_bytes = 1;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};

class Jb : public Command {
public:
	Jb() {
		occupied_bytes = 2;
	}
	virtual int calculateOffset() override;
	virtual std::string defineBytecode() override;
};