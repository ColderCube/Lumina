// Lumina.cpp : Defines the entry point for the application.
//

#include <Lumina.h>
#include <Lexer/Lexer.h>

int main() {
	//std::cout << "Hello CMake." << std::endl;
	//std::fstream f("source.ln");
	Lexer l("E:/Project_Compiler_Lumina/Lumina/source.ln");
	Token* t = l.getNextToken();
	while (t->tag != Tag::EOF_ && t->tag != Tag::UNIDENTIFIED) {
		t->print();
		t = l.getNextToken();
	}
	return 0;
}
