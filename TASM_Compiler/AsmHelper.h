#pragma once
#include <iostream>
#include <algorithm>
#include <regex>
#include <sstream>
#include <map>

std::string intToHex(int digit); 
std::string binToHex(std::string digit);
std::string octToHex(std::string digit);
std::string beautyBytes(std::string str, int number);
bool isRegister16(std::string _register);
bool isRegister8(std::string _register);
bool isConstant(std::string constant); 
bool isConstant16(std::string constant);
bool isConstant8(std::string constant);
bool isMemoryShift(std::string memory);
bool isRegShift(std::string memory);
bool isBin(std::string digit);
bool isDec(std::string digit);
bool isOct(std::string digit);
bool isHex(std::string digit);
std::string modrmRegReg(std::string operand1, std::string operand2);
std::string modrmMemShift(std::string operand1);
std::string modrmRegMemShift(std::string operand1, std::string operand2);
std::string modrmRegMem(std::string operand1);
std::string modrmMemShiftReg(std::string operand1, std::string operand2);
std::string modrmMemReg(std::string operand1);

const std::string commands =  "SCASB|INC|DEC|CMP|OR|AND|MOV|ADD|JB" ;
const std::string directives =  "DB|DW|DD|SEGMENT|MACRO|ENDS|ENDM|END|WORD|PTR" ;
const std::string registers =  "[ABCD]X|[ABCD]H|[ABCD]L|SI|DI|BP|SP|DS|ES|CS|SS" ;