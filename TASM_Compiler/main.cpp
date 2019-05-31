#include "Lexical.h"
#include "Syntaxer.h"
#include "Offset.h"
#include "ByteCode.h"
#include "MacroHandle.h"

int main(){

	fileChanger("source.asm");
	Lexical lexical("test.txt");

	lexical.start();
	//lexical.print();

	Syntaxer syntaxer(&lexical);
	syntaxer.start();
	//syntaxer.print();

	Offset offset(&syntaxer);
	offset.first_through();
	ByteCode bytecode(&offset);
	bytecode.second_through();
	offset.print();

	system("pause");
}