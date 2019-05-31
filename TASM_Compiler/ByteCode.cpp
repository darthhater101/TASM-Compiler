#include "ByteCode.h"

void ByteCode::second_through()
{
	int i = 0;
	bool skip = false;
	for (auto x : offset->sline->synline) {
		
		if (x.dmp.lxms.size() == 1) {
			if (x.dmp.lxms[0].word == "ENDM" && x.dmp.lxms[0].type == DIRECTIVE) {
				skip = false;
				i++;
				continue;
			}
		}

		if (skip) {
			i++;
			continue;
		}

		if (x.dmp.lxms.size() >= 2) {
			if ((x.dmp.lxms[1].word == "DB" || x.dmp.lxms[1].word == "DW" || x.dmp.lxms[1].word == "DD") && x.dmp.lxms[1].type == DIRECTIVE) {
				DataDir datadir(x);
				offset->oline[i].modrm = datadir.byteCode();
			}

			if (x.dmp.lxms[1].word == "MACRO" && x.dmp.lxms[1].type == DIRECTIVE) {
				skip = true;
			}
		}

		

		if (x.dmp.lxms[0].type == COMMAND) {
			Command* command = new UnknownCmd();
			Command* command2 = command->canGet(x.dmp.lxms[0].word);
			command2->takeDataheap(&offset->dataheap);
			command2->takeOffset(offset->oline[i].offset);
			command2->recognizeOperands(x);
			offset->oline[i].modrm += command2->defineBytecode();
		}


		i++;
	}
}
