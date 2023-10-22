#pragma once


namespace ErrorHandler {

	void LexerError(const char* msg, uint32_t line, uint32_t col) {
		std::cout << "Error : " << msg << "at line " << line << ":" << col;
	}


};