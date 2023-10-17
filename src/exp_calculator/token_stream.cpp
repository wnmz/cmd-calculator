#include "exp_calculator.h"

Token TokenStream::get_token() {
	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	stream >> ch;

	if (stream.eof()) {
		return Token(Token::EXIT_FLAG);
	}

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
		stream.putback(ch);
		double val;
		stream >> val;
		return Token(Token::Types::NUMBER, val);
	}
	case '[':
	{
		std::string exp;
		while ((stream >> ch) && ch != ']' && ch != ';') {
			exp += ch;
		}
		if (ch == ';') {
			stream.putback(ch);
		}
		return Token(Token::Types::FUNC_EXPRESSION, exp);
	}

	default: // handle keywords (let, sqrt)
		if (isalpha(ch)) {
			stream.putback(ch);

			std::string s;
			while (stream.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			stream.putback(ch);

			// Keywords handling
			Token::Types token_type = Token::get_type_by_name(s);
			if (token_type != Token::UNKNOWN) {
				prev_type = token_type;
				return Token(token_type);
			}

			// keywords args handling
			switch (prev_type) {
				case Token::VAR_DEF:
				{
					return Token(Token::Types::VAR_NAME, s);
				}
			}

			return Token(Token::UNKNOWN, s);
		}
		else {
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

void TokenStream::ignore() {
	Token t = get_token();
	while (t.type != Token::EXPRESSION_END_FLAG) t = get_token();
}
