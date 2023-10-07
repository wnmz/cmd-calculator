#include "exp_calculator.h"

Token TokenStream::get_token() {
	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	std::cin >> ch;

	switch (ch) {
	case ';':
	case 'q':
	case '(':
	case ')': 
	case '+': 
	case '-': 
	case '*': 
	case '/':
	case '=':
	case '^':
		return Token(static_cast<Token::Types>(ch));
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);
		double val;
		std::cin >> val;          
		return Token(Token::Types::NUMBER, val); 
	}
	default: // handle keywords (let, sqrt)
		if (isalpha(ch)) {
			std::cin.putback(ch);
			std::string s;
			while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			std::cin.putback(ch);
			
			if (s == Token::get_token_name(Token::Types::VAR_DEF)) 
				return Token(Token::Types::VAR_DEF);

			if (s == Token::get_token_name(Token::Types::SQRT_FUNC))
				return Token(Token::Token::SQRT_FUNC);

			return Token(Token::Types::VAR_NAME, s);
		} else {
			throw std::runtime_error("Bad token");
		}
	}
}

void TokenStream::put_back(Token t) {
	if (full) {
		throw std::runtime_error("put_back() into full buffer");
	}
	buffer = t;
	full = true;
}
