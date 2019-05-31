#include "Offset.h"
#define watch(x) std::cout<<x<<std::endl;

void Offset::first_through()
{
	int offset = 0;
	bool skip = false;
	bool is_seg = true;
	bool is_data = true;
	for (auto x : sline->synline) {

		offsetLine off;
		if (!is_seg || dataheap.macros.find(x.dmp.lxms[0].word) != dataheap.macros.end()) {
			if (x.dmp.lxms.size() >= 2 && x.dmp.lxms[1].word == "SEGMENT") {
				off.push(x, "0000");
			}
			else {
				off.push(x, "");
			}
		}
		else {
			off.push(x, beautyBytes(intToHex(offset), 4));
		}
		oline.push_back(off);

		if (x.dmp.lxms.size() == 1) {
			if (x.dmp.lxms[0].word == "ENDM" && x.dmp.lxms[0].type == DIRECTIVE) {
				skip = false;
				continue;
			}
		}

		if (skip) {
			continue;
		}

		if (x.dmp.lxms.size() >= 2) {

			if (x.dmp.lxms[0].type == USERS && x.dmp.lxms[1].word == ":") {
				dataheap.labels.insert(std::pair<std::string, int>(x.dmp.lxms[0].word, offset));
			}

			if (x.dmp.lxms[1].word == "SEGMENT" && x.dmp.lxms[1].type == DIRECTIVE) {
				offset = 0;
				is_seg = true;
			}

			if ((x.dmp.lxms[1].word == "DB" || x.dmp.lxms[1].word == "DW" || x.dmp.lxms[1].word == "DD") && x.dmp.lxms[1].type == DIRECTIVE) {
				DataDir datadir(x);
				if (is_data) {
					dataheap.data.insert(std::pair<std::string, int>(x.dmp.lxms[0].word, offset));
				}
				else {
					dataheap.code_data.insert(std::pair<std::string, int>(x.dmp.lxms[0].word, offset));
				}
				dataheap.data_size.insert(std::pair<std::string, std::string>(x.dmp.lxms[0].word, x.dmp.lxms[1].word));
				offset += datadir.calculateOffset();
			}
			if (x.dmp.lxms[1].word == "MACRO" && x.dmp.lxms[1].type == DIRECTIVE) {
				skip = true;
				dataheap.macros.insert(std::pair<std::string, int>(x.dmp.lxms[0].word, offset));
			}
			if (x.dmp.lxms[1].word == "ENDS" && x.dmp.lxms[1].type == DIRECTIVE) {
				offset = 0;
				is_seg = false;
				is_data = false;
			}
		}

		if (x.dmp.lxms[0].type == COMMAND) {
			Command* command = new UnknownCmd();
			Command* command2 = command->canGet(x.dmp.lxms[0].word);
			command2->takeDataheap(&dataheap);
			command2->recognizeOperands(x);
			offset += command2->calculateOffset();
		}


	}
}

void Offset::print()
{
	for (auto x : oline) {
		x.print();
	}
}
