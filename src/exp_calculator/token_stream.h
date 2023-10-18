#pragma once
#include <istream>
#include "token.h"

class TokenStream {
private:
	std::istream stream;
	bool full;
	Token::Types prev_type;
	Token buffer;
public:
	TokenStream(std::istream& str) :
		stream(str.rdbuf()),
		prev_type(Token::UNKNOWN),
		full(false),
		buffer(Token::EXIT_FLAG) {};
	Token get_token();
	void put_back(Token t);
	void ignore();
};