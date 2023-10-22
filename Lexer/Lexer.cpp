#include <Lexer/Lexer.h>

Lexer::Lexer(std::string file) {
	this->file = std::make_unique<std::fstream>(file, std::ios::in);
	create_reserved();
}

Token* Lexer::getNextToken() {
	if (file->eof()) {
		file->close();
		return new Token(Tag::EOF_);
	}
	for (; !file->eof() || peek == '\0'; readch()) {
		if (peek == ' ' || peek == '\t' || peek == '\n')
			continue;
		break;
	}
	if (peek == '\0' || peek < 0 || file->eof()) {
		file->close();
		return new Token(Tag::EOF_);
	}
	switch (peek) {
	case '&': {
		if (match('&')) {
			readch();
			return new Token(Tag::AND, "&&");
		} else {
			return new Token(Tag::BIT_AND, "&");
		}
	}
	case '|': {
		if (match('|')) {
			readch();
			return new Token(Tag::OR, "||");;
		} else {
			return new Token(Tag::BIT_OR, "|");
		}
	}
	case '=': {
		if (match('=')) {
			readch();
			return new Token(Tag::EQ, "==");;
		} else {
			return new Token(Tag::ASSIGN, "=");
		}
	}
	case '!': {
		if (match('=')) {
			readch();
			return new Token(Tag::NE, "!=");
		} else {
			return new Token(Tag::NOT, "!");
		}
	}
	case '<': {
		if (match('=')) {
			readch();
			return new Token(Tag::LE, "<=");
		} else {
			return new Token(Tag::LT, "<");
		}
	}
	case '>': {
		if (match('=')) {
			readch();
			return new Token(Tag::GE, ">=");
		} else {
			return new Token(Tag::GT, ">");
		}
	}
	case '+': {
		;
		readch();
		return new Token(Tag::PLUS, "+");
	}
	case '-': {
		readch();
		return new Token(Tag::MINUS, "-");
	}
	case '*': {
		readch();
		return new Token(Tag::MULTIPLY, "*");
	}
	case '/': {
		if (match('/')) {
			while (peek != '\n')
				readch();
			return getNextToken();
		}
		return new Token(Tag::DIVIDE, "/");
	}
	case '(': {
		readch();
		return new Token(Tag::LPARAN, "(");
	}
	case ')': {
		readch();
		return new Token(Tag::RPARAN, ")");
	}
	case '[': {
		readch();
		return new Token(Tag::RSBRAC, "[");
	}
	case ']': {
		readch();
		return new Token(Tag::LSBRAC, "]");
	}
	case '{': {
		readch();
		return new Token(Tag::RCBRAC, "{");
	}
	case '}': {
		readch();
		return new Token(Tag::LCBRAC, "}");
	}
	case '\'': {
		char charac;
		readch();
		charac = peek;
		if (!match('\'')) {
			std::cerr << "The closing \"\'\" is missing at line" << line_number
				<< "character " << char_number << std::endl;
			return getNextToken();
		}
		readch();
		return new Token(Tag::CHARA, charac);
	}
	case '\"': {
		readch();
		std::string str;
		while (peek != '\"' && peek != '\n') {
			str += peek;
			readch();
		}
		if (match('\"') != 0) {
			std::cerr << "The closing \"\"\" is missing at line" << line_number
				<< "character " << char_number << std::endl;
			return getNextToken();
		}
		readch();
		return new Token(Tag::STRING, str);
	}
	}
	if (std::isdigit(peek)) {
		int v = 0;
		do {
			v = v * 10 + (peek - '0');
			readch();
		} while (std::isdigit(peek));
		if (peek != '.') {
			return new Token(Tag::NUM, v);
		}
		float x = v;
		float d = 10;
		for (;;) {
			readch();
			if (!(std::isdigit(peek)))
				break;
			x = x + (peek - '0') / d;
			d = d * 10;
		}
		return new Token(Tag::REAL, x);
	}
	if (std::isalpha(peek) || peek == '_') {
		std::string str;
		do {
			str += peek;
			readch();
		} while (std::isalnum(peek) || peek == '_');
		for (auto i : reserved) {
			if (i.first == str) {
				return i.second;
			}
		}
		if (str == "int" || str == "float" || str == "char" || str == "bool") {

			return new Token(Tag::DATATYPE, str);
		}
		if (str == "true") {
			return new Token(Tag::TRUE, str);
		}
		if (str == "false") {
			return new Token(Tag::FALSE, str);
		}
		return new Token(Tag::ID, str);
	}
	if (peek == ';') {
		readch();
		return new Token(Tag::SEMI, ";");
	}
	if (peek == ',') {
		readch();
		return new Token(Tag::COMA, ",");
	}
	if (peek == ':') {
		readch();
		return new Token(Tag::COLON, ":");
	}
	std::cerr << "Found Unknown at " << line_number << ":" << char_number
		<< std::endl;
	return new Token(Tag::UNIDENTIFIED);
}

void Lexer::create_reserved() {
	reserve(Tag::IF, "if");
	reserve(Tag::ELSE, "else");
	reserve(Tag::WHILE, "while");
	reserve(Tag::DO, "do");
	reserve(Tag::BREAK, "break");
	reserve(Tag::FN, "fn");
}
void Lexer::reserve(Tag t, std::string lexeme) {
	reserved[lexeme] = new Token(t, lexeme);
}
void Lexer::readch() {
	file->get(peek);
	total_char++;
	char_number++;
	if (peek == '\n') {
		line_number++;
		char_number = 0;
	}
}
bool Lexer::match(char c) {
	readch();
	if (peek == c)
		return true;
	return false;
}
char Lexer::getpeek() {
	return peek;
}