#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iomanip>

class Token {
public:
	enum Types {
		NUMBER = '0',

		VAR_DEF,
		VAR_NAME,

		SQRT_FUNC,

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
	};

	static const std::unordered_map<Types, std::string> token_map;
	static std::string get_token_name(Types type);

	Types type;
	std::string name;
	double value;

	Token(Types t, double val) : type(t), value(val) {};
	Token(Types t) : type(t), value(0) {};
	Token(Types t, std::string n) : type(t), name(n), value(0) {};
};

class TokenStream {
private:
	bool full;
	Token buffer;
public:
	TokenStream() : full(false), buffer(Token::EXIT_FLAG) {};
	Token get_token();
	void put_back(Token t);
};

class VariableTable {
private:
	std::unordered_map<std::string, double> vars;
public:
	void define(std::string name, double var) {
		vars[name] = var;
	}

	double get(std::string name) {
		return vars[name];
	}

	bool has(std::string name) {
		return vars.find(name) != vars.end();
	}
};

class Calculator {
	VariableTable var_table;
	TokenStream ts;
	double val;
	double expression(); // * / ops
	double term(); // + - ops
	double primary(); // return numbers or variable values and handles brackets
	double statement(); // split variable declaration and expression
	double declaration(); // let name = [expression]
	double power(); // power (^) operator
	double sqrt(); // sqrt func
public:
	Calculator();

	int calculate();
	void add_const(const std::string str, double val);
	// returns error code (0 - Ok, 1 - expected error, 2 - unexpected)
};
