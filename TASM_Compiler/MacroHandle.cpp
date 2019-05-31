#include "MacroHandle.h"
#include <vector>
#include <fstream>
#include <string>

void fileChanger(std::string _file) 
{
	std::ifstream file(_file);
	std::ofstream out("test.txt");

	out.clear();

	std::string macroName = "";
	std::vector<std::string> macro_lines;
	std::string macroParam = "";
	std::string existParam = "";

	bool isMacro = false;

	std::string line;

	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		out << line << std::endl;

		if (line.find("ENDM") != std::string::npos) {
			isMacro = false;
		}

		if (isMacro) {
			macro_lines.push_back(line);
		}

		if (line.find("MACRO") != std::string::npos) {
			for (auto x : line) {
				if (x == ' ') {
					break;
				}
				macroName.push_back(x);
			}

			for (int i = line.size() - 1; line[i] != ' '; i--) {
				macroParam.push_back(line[i]);
			}

			reverse(macroParam.begin(), macroParam.end());
			isMacro = true;
		}


		if (line.find(macroName) != std::string::npos) {
			for (int i = line.size() - 1; line[i] != ' '; i--) {
				existParam.push_back(line[i]);
			}
			reverse(existParam.begin(), existParam.end());
			for (auto x : macro_lines) {
				if (x.find(macroParam) != std::string::npos) {
					x.erase(x.find(macroParam), macroName.size());
					x += existParam;
				}
				out << x << std::endl;
			}
			existParam.clear();
		}


	}
}
