#pragma once
#include <unordered_map>
#include <string>

class Token {
public:
	enum Types {
		NUMBER = '0',

		VAR_DEF,
		VAR_NAME,

		SQRT_FUNC_DEF,
		ABS_FUNC_DEF,
		SIN_FUNC_DEF,
		COS_FUNC_DEF,

		FUNC_DEF,
		FUNC_EXPRESSION,
		FUNC_PRINT_FROM,
		FUNC_PRINT_TO,
		FUNC_PRINT_STEP,

		OP_PLUS = '+',
		OP_MINUS = '-',
		OP_MULT = '*',
		OP_DIVIDE = '/',
		OP_EQUAL = '=',
		OP_POWER = '^',

		OPEN_BRACKET = '(',
		CLOSING_BRACKET = ')',

		EXIT_FLAG = 'q',
		EXPRESSION_END_FLAG = ';',

		UNKNOWN = -1,
	};

	Types type;
	double value;
	std::string str_val;

	Token(Types t, double val) : type(t), value(val) {};
	Token(Types t) : type(t), value(0) {};
	Token(Types t, std::string n) : type(t), str_val(n), value(0) {};

	static const std::unordered_map<Types, std::string> token_map;
	static std::string get_token_name(Types type);
	static Types get_type_by_name(std::string name);
};
