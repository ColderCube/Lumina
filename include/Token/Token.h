#pragma once
#include <variant>

#include <Token/Tag.h>


template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

class Token {
public:
	std::variant<int, char, double, std::string> val;
	Tag tag;
public:
	Token(Tag t) : tag(t), val("") {};
	Token(Tag t, std::variant<int, char, double, std::string> value) : tag(t), val(value) {};
	~Token() { delete this; }
	void print() { 
		std::cout << as_integer(tag) << '\t'; 
		std::visit([](auto arg) {std::cout << arg << " "; }, val); 
		std::cout << std::endl; 
	}
};