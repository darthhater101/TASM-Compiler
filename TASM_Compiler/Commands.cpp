#include "Commands.h"

OPERTYPE Command::operandType(std::string operand)
{
	if (std::regex_match(operand, std::regex(registers))) {
		return REG;
	}
	if (isdigit(operand[0])) {
		return IMM;
	}

	return MEM;
}

void Command::recognizeOperands(synDump dump)
{
	if (dump.arg_index_1 == -1 && dump.arg_index_2 == -1) {
		first = "";
		second = "";
	}
	if (dump.arg_index_1 != -1 && dump.arg_index_2 == -1) {
		for (int i = dump.arg_index_1 - 1; i < dump.arg_index_1 + dump.arg_size_1 - 1; i++) {
			first += dump.dmp.lxms[i].word;
			if (dump.dmp.lxms[i].type == DIRECTIVE) {
				first += " ";
			}
		}
	}
	if (dump.arg_index_1 != -1 && dump.arg_index_2 != -1) {
		for (int i = dump.arg_index_1 - 1; i < dump.arg_index_1 + dump.arg_size_1 - 1; i++) {
			first += dump.dmp.lxms[i].word;
		}
		for (int i = dump.arg_index_2 - 1; i < dump.arg_index_2 + dump.arg_size_2 - 1; i++) {
			second += dump.dmp.lxms[i].word;
		}
	}
}

Command * Command::canGet(std::string cmd)
{
	if (cmd == "SCASB") {
		return new Scasb();
	}
	if (cmd == "INC") {
		return new Inc();
	}
	if (cmd == "DEC") {
		return new Dec();
	}
	if (cmd == "CMP") {
		return new Cmp();
	}
	if (cmd == "OR") {
		return new Or();
	}
	if (cmd == "AND") {
		return new And();
	}
	if (cmd == "ADD") {
		return new Add();
	}
	if (cmd == "MOV") {
		return new Mov();
	}
	if (cmd == "JB") {
		return new Jb();
	}
}

void Command::takeDataheap(DataHeap * _dataheap)
{
	dataheap = _dataheap;
}

void Command::takeOffset(std::string _offset)
{
	_offset.erase(0, 2);
	offset = std::stoi(_offset, 0, 16);
}

int Scasb::calculateOffset()
{
	return occupied_bytes;
}

std::string Scasb::defineBytecode()
{
	return "AE";
}

int Inc::calculateOffset()
{
	if (isRegister8(first)) {
		occupied_bytes++;
	}
	return occupied_bytes;
}

std::string Inc::defineBytecode()
{
	std::string byte_code = "";

	int modRm = 40;
	if (isRegister16(first)) {
		if (first == "AX") {
			modRm += 0;
		}
		if (first == "CX") {
			modRm += 1;
		}
		if (first == "DX") {
			modRm += 2;
		}
		if (first == "BX") {
			modRm += 3;
		}
		if (first == "SP") {
			modRm += 4;
		}
		if (first == "BP") {
			modRm += 5;
		}
		if (first == "SI") {
			modRm += 6;
		}
		if (first == "DI") {
			modRm += 7;
		}

		byte_code += std::to_string(modRm);
	}
	if (isRegister8(first)) {
		byte_code += "FE ";
		byte_code += modrmRegReg("AX", first);
	}


	return byte_code;
}

int Dec::calculateOffset()
{
	if (isMemoryShift(first)) {
		occupied_bytes += 0;
	}
	else {
		occupied_bytes += 2;
	}

	return occupied_bytes;
}

std::string Dec::defineBytecode()
{
	std::string byte_code = "";

	if (isMemoryShift(first)) {
		std::string dir = "";
		std::string main_oper = "";
		int i = 0;
		while (first[i] != ' ') {
			dir.push_back(first[i]);
			i++;
		}

		i = first.size() - 1;

		while (first[i] != ' ') {
			main_oper.push_back(first[i]);
			i--;
		}

		std::reverse(main_oper.begin(), main_oper.end());

		if (dir == "BYTE") {
			byte_code += "FE ";
		}
		if (dir == "WORD") {
			byte_code += "FF ";
		}

		byte_code += beautyBytes(modrmMemShift(main_oper), 2);

	}
	else {
		if (dataheap->data_size[first] == "DB") {
			byte_code += "FE ";
		}
		if (dataheap->data_size[first] == "DW") {
			byte_code += "FF ";
		}
		byte_code += "0E ";
		if (dataheap->code_data.find(first) != dataheap->code_data.end()) {
			byte_code += intToHex(dataheap->code_data[first]) + "r";
		}

		if (dataheap->data.find(first) != dataheap->data.end()) {
			byte_code += beautyBytes(intToHex(dataheap->data[first]), 4) + "r";
		}
	}

	return byte_code;
}

int Cmp::calculateOffset()
{
	return occupied_bytes;
}

std::string Cmp::defineBytecode()
{
	std::string byte_code = "";

	if (isRegister16(first) && isRegister16(second)) {
		byte_code += "3B ";
	}
	if (isRegister8(first) && isRegister8(second)) {
		byte_code += "3A ";
	}

	byte_code += modrmRegReg(first, second);

	return byte_code;
}

int Or::calculateOffset()
{
	if (isMemoryShift(second)) {
		occupied_bytes += 0;
	}
	else {
		occupied_bytes += 2;
	}
	return occupied_bytes;
}

std::string Or::defineBytecode()
{
	std::string byte_code = "";

	if (isMemoryShift(second)) {
		std::string dir = "";
		std::string main_oper = "";
		int i = 0;
		while (second[i] != ' ') {
			dir.push_back(second[i]);
			i++;
		}

		i = second.size() - 1;

		while (second[i] != ' ') {
			main_oper.push_back(second[i]);
			i--;
		}

		std::reverse(main_oper.begin(), main_oper.end());

		if (dir == "BYTE") {
			byte_code += "0A ";
		}
		if (dir == "WORD") {
			byte_code += "0B ";
		}

		byte_code += beautyBytes(modrmMemShift(main_oper), 2);

	}
	else {
		byte_code += "0B ";
		byte_code += beautyBytes(modrmRegMem(first), 2) + " ";
		if (dataheap->code_data.find(second) != dataheap->code_data.end()) {
			byte_code += intToHex(dataheap->code_data[second]) + "r";
		}

		if (dataheap->data.find(second) != dataheap->data.end()) {
			byte_code += beautyBytes(intToHex(dataheap->data[second]), 4) + "r";
		}
	}

	return byte_code;
}

int Mov::calculateOffset() //reg/imm
{
	if (isConstant(second)) {
		if (isRegister8(first)) {
			occupied_bytes += 1;
		}
		if (isRegister16(first)) {
			occupied_bytes += 2;
		}
	}

	if (isMemoryShift(second)) {
		if (isRegShift(second)) {
			occupied_bytes += 1;
		}

		if (second.find(":") != std::string::npos) {
			std::string segReg = "";
			for (auto x : second) {
				if (x == ':') {
					break;
				}
				segReg.push_back(x);
			}

			if (segReg == "DS") {
				occupied_bytes += 1;
			}
			else {
				occupied_bytes += 2;
			}
		}

	}

	return occupied_bytes;
}

std::string Mov::defineBytecode()
{
	std::string byte_code = "";

	if (isConstant(second)) {
		if (isConstant8(second)) {
			int modRm = 176;
			if (first == "AL") {
				modRm += 0;
			}
			if (first == "CL") {
				modRm += 1;
			}
			if (first == "DL") {
				modRm += 2;
			}
			if (first == "BL") {
				modRm += 3;
			}
			if (first == "AH") {
				modRm += 4;
			}
			if (first == "CH") {
				modRm += 5;
			}
			if (first == "DH") {
				modRm += 6;
			}
			if (first == "BH") {
				modRm += 7;
			}
			byte_code += intToHex(modRm) + " ";

			second.pop_back();

			if(isRegister16)
				byte_code += beautyBytes(second, 4);

		}
		if (isConstant16(second)) {
			int modRm = 184;
			if (first == "AX") {
				modRm += 0;
			}
			if (first == "CX") {
				modRm += 1;
			}
			if (first == "DX") {
				modRm += 2;
			}
			if (first == "BX") {
				modRm += 3;
			}
			if (first == "SP") {
				modRm += 4;
			}
			if (first == "BP") {
				modRm += 5;
			}
			if (first == "SI") {
				modRm += 6;
			}
			if (first == "DI") {
				modRm += 7;
			}

			byte_code += intToHex(modRm) + " ";

			second.pop_back();

			byte_code += beautyBytes(second, 4);

		}
	}
	if (isMemoryShift(second)) {
		if (isRegShift(second)) {
			if (isRegister8(first)) {
				byte_code += "8A ";
			}
			if (isRegister16(first)) {
				byte_code += "8B ";
			}
			byte_code += beautyBytes(modrmRegMemShift(first, second), 2);
		}
		if (second.find(":") != std::string::npos) {
			std::string segReg = "";
			std::string main_oper = "";
			for (auto x : second) {
				if (x == ':') {
					break;
				}
				segReg.push_back(x);
			}

			for (int i = second.size() - 1; second[i] != ':'; i--) {
				main_oper.push_back(second[i]);
			}

			std::reverse(main_oper.begin(), main_oper.end());

			if (segReg == "DS") {
				byte_code += "";
			}
			if (segReg == "ES") {
				byte_code += "26: ";
			}
			if (segReg == "CS") {
				byte_code += "2E: ";
			}
			if (segReg == "SS") {
				byte_code += "36: ";
			}
			if (segReg == "GS") {
				byte_code += "65: ";
			}
			if (segReg == "FS") {
				byte_code += "64: ";
			}

			byte_code += "8B ";
			byte_code += beautyBytes(modrmRegMemShift(first, main_oper), 2);
		}
	}


	return byte_code;
}

int Jb::calculateOffset()
{
	
	if (dataheap->labels.find(first) != dataheap->labels.end()) {
		occupied_bytes += 0;
	}
	else {
		occupied_bytes += 2;
	}
	return occupied_bytes;
}

std::string Jb::defineBytecode()
{
	std::string byte_code = "";

	byte_code += "72 ";

	if (offset > dataheap->labels[first]) {
		int num = 255 - (offset - dataheap->labels[first]) - 1;
		byte_code += intToHex(num);
	}
	if (offset < dataheap->labels[first]) {
		byte_code += beautyBytes(intToHex(dataheap->labels[first] - offset - 2), 2);
		byte_code += " 90 90";
	}

	return byte_code;
}

int Add::calculateOffset()
{
	if (isMemoryShift(first)) {
		occupied_bytes += 0;
	}
	else {
		occupied_bytes += 2;
	}

	if (isConstant16(second)) {
		occupied_bytes += 2;
	}
	if (isConstant8(second)) {
		occupied_bytes += 1;
	}

	return occupied_bytes;
}

std::string Add::defineBytecode()
{
	std::string byte_code = "";

	if (dataheap->data_size.find(first) != dataheap->data_size.end()) {
		if (dataheap->data_size[first] == "DB" && isConstant8(second)) {
			byte_code += "80 ";
		}
		if (dataheap->data_size[first] == "DW" && isConstant16(second)) {
			byte_code += "81 ";
		}
		if (dataheap->data_size[first] == "DW" && isConstant8(second)) {
			byte_code += "83 ";
		}
	}

	byte_code += "06 ";
	if (dataheap->code_data.find(first) != dataheap->code_data.end()) {
		byte_code += intToHex(dataheap->code_data[first]) + "r";
	}

	if (dataheap->data.find(first) != dataheap->data.end()) {
		byte_code += beautyBytes(intToHex(dataheap->data[first]), 4) + "r";
	}

	byte_code += " ";

	second.pop_back();
	byte_code += second;

	return byte_code;
}

int And::calculateOffset()
{
	if (isMemoryShift(first)) {
		occupied_bytes += 0;
	}
	else {
		occupied_bytes += 2;
	}
	return occupied_bytes;
}

std::string And::defineBytecode()
{
	std::string byte_code = "";

	if (isMemoryShift(first)) {
		std::string dir = "";
		std::string main_oper = "";
		int i = 0;
		while (first[i] != ' ') {
			dir.push_back(first[i]);
			i++;
		}

		i = first.size() - 1;

		while (first[i] != ' ') {
			main_oper.push_back(first[i]);
			i--;
		}

		std::reverse(main_oper.begin(), main_oper.end());

		if (dir == "BYTE") {
			byte_code += "20 ";
		}
		if (dir == "WORD") {
			byte_code += "21 ";
		}

		byte_code += beautyBytes(modrmMemShiftReg(main_oper, second), 2);

	}
	else {
		byte_code += "21 ";
		byte_code += beautyBytes(modrmMemReg(second), 2) + " ";
		if (dataheap->code_data.find(first) != dataheap->code_data.end()) {
			byte_code += intToHex(dataheap->code_data[first]) + "r";
		}

		if (dataheap->data.find(first) != dataheap->data.end()) {
			byte_code += beautyBytes(intToHex(dataheap->data[first]), 4) + "r";
		}
	}

	return byte_code;
}
