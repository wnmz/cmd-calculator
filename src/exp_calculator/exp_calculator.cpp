#include "exp_calculator.h"

using namespace std;

const unordered_map<Token::Types, std::string> Token::token_map = {
	{Token::Types::VAR_DEF, "let"},
	{Token::Types::VAR_NAME, "var_name"},
	{Token::Types::SQRT_FUNC, "sqrt"},
};

std::string Token::get_token_name(Token::Types type) {
	auto it = Token::token_map.find(type);
	if (it != Token::token_map.end()) {
		return it->second;
	} else {
		return "Unknown";
	}
}

double Calculator::primary()
{
	Token t = ts.get_token();
	switch (t.type)
	{
	case Token::SQRT_FUNC:
		return sqrt();
		
	case Token::Types::OPEN_BRACKET:
	{
		double d = expression();
		t = ts.get_token();
		if (t.type != Token::Types::CLOSING_BRACKET)
			throw std::runtime_error("closing bracket expected");
		return d;
	}
	case Token::Types::NUMBER:
		return t.value;

	case Token::Types::OP_MINUS:
	{
		double val = expression();
		return -val;
	}

	default:
		if (var_table.has(t.name)) {
			return var_table.get(t.name);
		}
		else {
			throw std::runtime_error("primary expected");
		}
	}
};

double Calculator::power() {
	double left = primary();
	Token t = ts.get_token();
	if (t.type == Token::Types::OP_POWER) {
		double exponent = primary();
		return std::pow(left, exponent);
	} else {
		ts.put_back(t);
		return left;
	}
}

double Calculator::term()
{
	double left = power();
	Token t = ts.get_token();

	while (true)
	{
		switch (t.type)
		{
		case Token::Types::OP_MULT:
			left *= power();
			t = ts.get_token();
			break;
		case Token::Types::OP_DIVIDE:
		{
			double d = power();
			if (d == 0)
				throw std::runtime_error("division by zero");
			left /= d;
			t = ts.get_token();
			break;
		}
		default:
			ts.put_back(t);
			return left;
		}
	}
};
double Calculator::expression()
{
	double left = term();
	Token t = ts.get_token();
	while (true)
	{
		switch (t.type)
		{
		case Token::Types::OP_PLUS:
			left += term();
			t = ts.get_token();
			break;
		case Token::Types::OP_MINUS:
			left -= term();
			t = ts.get_token();
			break;
		default:
			ts.put_back(t);
			return left;
		}
	}
}

double Calculator::sqrt() {
    double sub = expression();
    if (sub < 0)
        throw std::runtime_error("square root of a negative number");
    return std::sqrt(sub);
}

double Calculator::declaration()
{
	// handles "let name = [expression]"

	Token t = ts.get_token();
	if (t.type != Token::Types::VAR_NAME)
		throw std::runtime_error("expected variable name in declaration");
	std::string name = t.name;

	Token t2 = ts.get_token();
	if (t2.type != Token::Types::OP_EQUAL)
		throw std::runtime_error("expected = after variable name");

	double d = expression();
	var_table.define(name, d);
	return d;
}

double Calculator::statement()
{
	Token t = ts.get_token();
	switch (t.type)
	{
	case Token::Types::VAR_DEF:
		return declaration();
	default:
		ts.put_back(t);
		return expression();
	}
}

int Calculator::calculate()
{
	std::cout << std::fixed;
	std::cout << "> " << std::flush;
	while (cin)
		try
		{
			Token t = ts.get_token();
			while (t.type == Token::Types::EXPRESSION_END_FLAG)
				t = ts.get_token();

			if (t.type == Token::Types::EXIT_FLAG)
				return 0;

			ts.put_back(t);

			cout << "= " << std::setprecision(4) << statement() << endl;
			std::cout << "> " << std::flush;
		}
		catch (exception &e)
		{
			cout << "Calculation error: " << e.what() << endl;
			return 1;
		}
		catch (...)
		{
			cout << "Unknown error!" << endl;
			return 2;
		}

	return 0;
}

void Calculator::add_const(const string str, double val) {
	this->var_table.define(str, val);
}

Calculator::Calculator() {
	add_const("pi", 3.14159265358979323846);
	add_const("e", 2.718281828459045235360);
}