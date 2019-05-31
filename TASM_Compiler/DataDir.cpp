#include "DataDir.h"

DataDir::DataDir(synDump synline) {
	name = synline.dmp.lxms[0].word;
	if (synline.dmp.lxms[1].word == "DB")
		size = DB;
	if (synline.dmp.lxms[1].word == "DW")
		size = DW;
	if (synline.dmp.lxms[1].word == "DD")
		size = DD;
	_value = synline.dmp.lxms[2].word;
	value_type = synline.dmp.lxms[2].type;
}

int DataDir::calculateOffset() {
	if (size == DB) {
		if (value_type == TEXT) {
			return _value.size();
		}
		return 1;
	}
	if (size == DW) {
		return 2;
	}
	if (size == DD) {
		return 4;
	}
}

std::string DataDir::byteCode() {
	int bit = 0;
	if (size == DB) {
		bit = 2;
		if (value_type == TEXT) {
			return stringHandle();
		}
	}
	if (size == DW) {
		bit = 4;
	}
	if (size == DD) {
		bit = 8;
	}

	std::string byte_code = "";
	if (isDec(_value)) {
		_value.pop_back();
		byte_code = intToHex(std::stoi(_value, 0, 10));
	}
	if (isHex(_value)) {
		_value.pop_back();
		byte_code = _value;
	}
	if (isOct(_value)) {
		_value.pop_back();
		byte_code = octToHex(_value);
	}
	if (isBin(_value)) {
		_value.pop_back();
		byte_code = binToHex(_value);
	}

	return beautyBytes(byte_code, bit);
}

std::string DataDir::stringHandle()
{
	std::string byte_code = "";
	int counter = 0;
	for (int i = 0; i < _value.size(); i++) {
		byte_code += intToHex((int)_value[i]) + " ";
		counter++;
		if (counter % 7 == 0) {
			//byte_code += "+";
			//byte_code += "\n";
		}
	}

	return byte_code;
}
