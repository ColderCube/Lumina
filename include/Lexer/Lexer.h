#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <memory>

#include <Token/Token.h>
#include <Token/Tag.h>


class Lexer {
public:
	uint32_t line_number = 0;
	uint32_t char_number = 0;
	uint32_t total_char = 0;

public:
	Lexer(std::string file);
	virtual ~Lexer() {  };
	Token* getNextToken();

private:
	char peek = ' ';
	std::unique_ptr<std::fstream> file;
	std::map<std::string, Token*> reserved;
	void create_reserved();
	void reserve(Tag t, std::string lexeme);
	void readch();
	bool match(char c);
	char getpeek();
};
