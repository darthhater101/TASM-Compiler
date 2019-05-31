#include "Lexical.h"
#include <fstream>
#include <string>
#include <regex>

void Lexical::start() {
	std::ifstream file(filename);

	std::string line;
	int num = 1;
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		dump dmp;
		dmp.push(parse(line), line, num++);
		dmps.push_back(dmp);
	}
}

std::vector<lexem> Lexical::parse(std::string line) {
	std::vector<lexem> lxms;
	std::string tmp;

	int i = 0;
	int id = 1;
	while (i < line.size()) {

		if (isalnum(line[i]) || line[i] == '\'' || line[i] == '_') {
			tmp.push_back(line[i]);
		}

		if (isspace(line[i])) {
			if (!tmp.empty()) {
				lexem lxm;
				lxm.push(id++, tmp, tmp.size(), lexem_type(tmp));
				lxms.push_back(lxm);
				tmp.clear();
			}
		}

		if (ispunct(line[i]) && line[i] != '\'' && line[i] != '_') {
			if (!tmp.empty()) {
				lexem lxm;
				lxm.push(id++, tmp, tmp.size(), lexem_type(tmp));
				lxms.push_back(lxm);
			}
			std::string ch;
			ch.push_back(line[i]);
			lexem c;
			c.push(++id, ch, ch.size(), OCHAR);
			lxms.push_back(c);
			tmp.clear();
			ch.clear();
		}

		if (i == line.size() - 1)
		{
			if (!tmp.empty()) {
				lexem lxm;
				lxm.push(id++, tmp, tmp.size(), lexem_type(tmp));
				lxms.push_back(lxm);
				tmp.clear();
			}
		}


		i++;
	}

	return lxms;
}

TYPE Lexical::lexem_type(std::string &word)
{
	TYPE type;
	if (word[0] == '\'' && word[word.length() - 1] == '\'') {
		type = TEXT;
		word.pop_back();
		word.erase(0, 1);
		return type;
	}
	else if (std::regex_match(word, std::regex(commands))) {
		type = COMMAND;
	}
	else if (std::regex_match(word, std::regex(directives))) {
		type = DIRECTIVE;
	}
	else if (std::regex_match(word, std::regex(registers))) {
		type = REGISTER;
	}
	else if (isdigit(word[0])) {
		type = DEC;
		if (word[word.length() - 1] == 'b') {
			type = BIN;
		}
		if (word[word.length() - 1] == 'd') {
			type = DEC;
		}
		if (word[word.length() - 1] == 'o') {
			type = OCT;
		}
		if (word[word.length() - 1] == 'h') {
			type = HEX;
		}
	}
	else {
		type = USERS;
	}

	return type;
}

void Lexical::print()
{
	for (auto x : dmps) {
		x.print();
		std::cout << std::endl;
	}
}
