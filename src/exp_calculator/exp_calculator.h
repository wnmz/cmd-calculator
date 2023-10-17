#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <sstream>

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
	std::string name;

	Token(Types t, double val) : type(t), value(val) {};
	Token(Types t) : type(t), value(0) {};
	Token(Types t, std::string n) : type(t), name(n), value(0) {};

	static const std::unordered_map<Types, std::string> token_map;
	static std::string get_token_name(Types type);
	static Types get_type_by_name(std::string name);
};

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
private:
	int prescision = 4;

	std::istream in_stream;
	std::ostream out_stream;
	VariableTable var_table;
	TokenStream ts;
	double expression(); // * / ops
	double term(); // + - ops
	double primary();
	double function(); // func [expression] from A to B step C
	// return numbers or variable values and handles brackets
	double statement(); // split variable declaration and expression
	double declaration(); // let name = [expression]
	double power(); // power (^) operator
	double sqrt(); // sqrt func
	double sin();
	double cos();
	double abs();
public: 
	// if output not defined it will be cout
	Calculator(std::istream& input_st);
	Calculator(std::istream& input_st, std::ostream& output_st);

	// returns error code (0 - Ok, 1 - expected error, 2 - unexpected)
	int calculate();

	void add_const(const std::string str, double val);
	void set_prescision(int n);
	int get_prescision();
};