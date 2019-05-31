#include "AsmHelper.h"

std::map<std::string, std::string> modRm{
	{"[SI]", "100"},
	{"[DI]", "101"},
	{"[BX]", "111"},
	{"[BX+SI]", "000"},
	{"[BX+DI]", "001"},
	{"[BP+SI]", "010"},
	{"[BP+DI]", "011"},
	{"AX", "000"},
	{"BX", "011"},
	{"CX", "001"},
	{"DX", "010"},
	{"AL", "000"},
	{"BL", "011"},
	{"CL", "001"},
	{"DL", "010"},
	{"AH", "100"},
	{"BH", "111"},
	{"CH", "101"},
	{"DH", "110"}
};

std::string intToHex(int digit) {
	std::string hex;
	std::stringstream ss;
	ss << std::hex << digit;
	hex = ss.str();

	std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);

	return hex;
}

std::string binToHex(std::string digit)
{
	if (isalpha(digit[digit.size() - 1])) {
		digit.pop_back();
	}
	return intToHex(std::stoi(digit, 0, 2));
}

std::string octToHex(std::string digit)
{
	if (isalpha(digit[digit.size() - 1])) {
		digit.pop_back();
	}
	return intToHex(std::stoi(digit, 0, 8));
}

std::string beautyBytes(std::string str, int number) {
	std::string bytes;
	while (bytes.length() < number - str.length())
	{
		bytes.push_back('0');
	}
	bytes += str;

	return bytes;
}

bool isRegister16(std::string _register) {
	if (std::regex_match(_register, std::regex("[ABCD]X"))) {
		return true;
	}
	return false;
}

bool isRegister8(std::string _register) {
	if (std::regex_match(_register, std::regex("[ABCD]H|[ABCD]L"))) {
		return true;
	}
	return false;
}

bool isConstant(std::string constant)
{
	if (isdigit(constant[constant.size() - 1])) {
		return true;
	}
	else if (constant[constant.size() - 1] == 'b' || constant[constant.size() - 1] == 'o' || constant[constant.size() - 1] == 'd' || constant[constant.size() - 1] == 'h') {
		return true;
	}
	else
		return false;

}

bool isConstant16(std::string constant) {
	constant.pop_back();
	int i = 0;
	while (constant[i] == '0')
		constant.erase(0, 1);
	if (constant.size() > 2) {
		return true;
	}

	return false;
}

bool isConstant8(std::string constant) {
	constant.pop_back();
	int i = 0;
	while (constant[i] == '0')
		constant.erase(0, 1);
	if (constant.size() <= 2) {
		return true;
	}

	return false;
}

bool isMemoryShift(std::string memory) {
	if (memory[0] == '[' && memory[memory.size() - 1] == ']') {
		return true;
	}
	if (memory[memory.size() - 1] == ']') {
		return true;
	}
	return false;
}

bool isRegShift(std::string memory)
{
	if (memory == "[SI]") {
		return true;
	}
	if (memory == "[DI]") {
		return true;
	}
	if (memory == "[BX]") {
		return true;
	}
	if (memory == "[BX+SI]") {
		return true;
	}
	if (memory == "[BX+DI]") {
		return true;
	}
	if (memory == "[BP+SI]") {
		return true;
	}
	if (memory == "[BP+DI]") {
		return true;
	}
	return false;
}

bool isBin(std::string digit) {
	if (digit[digit.size() - 1] == 'b') {
		return true;
	}
	return false;
}

bool isDec(std::string digit) {
	if (digit[digit.size() - 1] == 'd' || isdigit(digit[digit.size() - 1])) {
		return true;
	}
	return false;
}

bool isOct(std::string digit) {
	if (digit[digit.size() - 1] == 'o') {
		return true;
	}
	return false;
}

bool isHex(std::string digit) {
	if (digit[digit.size() - 1] == 'h') {
		return true;
	}
	return false;
}

std::string modrmRegReg(std::string operand1, std::string operand2)
{
	std::string modrm = "";
	
	modrm += "11";
	modrm += modRm[operand1];
	modrm += modRm[operand2];

	return binToHex(modrm);
}

std::string modrmMemShift(std::string operand1)
{
	std::string modrm = "";

	modrm += "00";
	modrm += modRm["CX"];
	modrm += modRm[operand1];

	return binToHex(modrm);
}

std::string modrmRegMemShift(std::string operand1, std::string operand2)
{
	std::string modrm = "";

	modrm += "00";
	modrm += modRm[operand1];
	modrm += modRm[operand2];

	return binToHex(modrm);
}

std::string modrmRegMem(std::string operand1)
{
	std::string modrm = "";

	modrm += "00";
	modrm += modRm[operand1];
	modrm += "110";

	return binToHex(modrm);
}

std::string modrmMemShiftReg(std::string operand1, std::string operand2)
{
	std::string modrm = "";

	modrm += "00";
	modrm += modRm[operand2];
	modrm += modRm[operand1];

	return binToHex(modrm);
}

std::string modrmMemReg(std::string operand1)
{
	std::string modrm = "";

	modrm += "00";
	modrm += modRm[operand1];
	modrm += "110";

	return binToHex(modrm);
}
