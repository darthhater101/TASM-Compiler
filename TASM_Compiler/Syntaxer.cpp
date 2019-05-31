#include "Syntaxer.h"

void Syntaxer::start() {
	for (auto& x : dmp->dmps) {
		synDump sdmp;
		int mnemo = -1;
		int msize = -1;
		int label = -1;
		int arg1id = -1;
		int arg2id = -1;
		int arg1size = -1;
		int arg2size = -1;

		if (x.lxms.size() == 1)
		{
			mnemo = 1;
			msize = 1;
		}
		if (x.lxms.size() == 2)
		{
			if (x.lxms[0].type == USERS && x.lxms[1].type == DIRECTIVE)
			{
				label = 1;
				mnemo = 2;
				msize = 1;
			}
			if (x.lxms[0].type == USERS && (x.lxms[1].type == REGISTER || x.lxms[1].type == USERS))
			{
				label = 1;
				arg1id = 2;
				arg1size = 1;
			}
			if (x.lxms[0].type == USERS && x.lxms[1].word == ":")
			{
				label = 1;
				arg1id = 2;
				arg1size = 1;
			}
			if (x.lxms[0].type == COMMAND)
			{
				mnemo = 1;
				msize = 1;
				arg1id = 2;
				arg1size = 1;
			}
		}
		if (x.lxms.size() >= 3)
		{
			if (x.lxms[0].type == USERS && x.lxms[1].type == DIRECTIVE)
			{
				label = 1;
				mnemo = 2;
				msize = 1;
				arg1id = 3;
				arg1size = 1;
			}
			if (x.lxms[0].type == COMMAND)
			{
				mnemo = 1;
				msize = 1;
				arg1id = 2;
				arg1size = 1;
				arg2id = 4;
				arg2size = x.lxms.size() - (arg2id - 1);
			}

			if (x.lxms[0].type == COMMAND && x.lxms[1].type == DIRECTIVE)
			{
				mnemo = 1;
				msize = 1;
				arg1id = 2;
				arg1size = x.lxms.size() - (arg1id - 1);
				arg2id = -1;
				arg2size = -1;
			}
		}

		sdmp.push(label, mnemo, msize, arg1id, arg1size, arg2id, arg2size, x);
		synline.push_back(sdmp);	
	}
}

void Syntaxer::print()
{
	for (auto x : synline) {
		x.print();
		std::cout << std::endl;
	}
}
