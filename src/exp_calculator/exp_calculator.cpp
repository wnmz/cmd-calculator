#include "exp_calculator.h"

using namespace std;

Calculator::Calculator(std::istream& st) : in_stream(st.rdbuf()), ts(st), out_stream(std::cout.rdbuf())
{
	add_const("pi", 3.14159265358979323846);
	add_const("e", 2.718281828459045235360);
};

Calculator::Calculator(std::istream& st, std::ostream& out) :
	in_stream(st.rdbuf()),
	ts(st),
	out_stream(out.rdbuf())
{
	add_const("pi", 3.14159265358979323846);
	add_const("e", 2.718281828459045235360);
};

double Calculator::primary()
{
	Token t = ts.get_token();
	switch (t.type)
	{
	case Token::Types::NUMBER:
		return t.value;

	case Token::Types::OP_MINUS:
	{
		double val = expression();
		return -val;
	}

	case Token::Types::OP_PLUS:
	{
		double val = expression();
		return val;
	}

	case Token::SQRT_FUNC_DEF:
		return this->sqrt();

	case Token::SIN_FUNC_DEF:
		return this->sin();

	case Token::COS_FUNC_DEF:
		return this->cos();

	case Token::ABS_FUNC_DEF:
		return this->abs();
		
	case Token::Types::OPEN_BRACKET:
	{
		double d = expression();
		t = ts.get_token();
		if (t.type != Token::Types::CLOSING_BRACKET)
			throw std::runtime_error("closing bracket expected");
		return d;
	}

	case Token::Types::EXPRESSION_END_FLAG:
		return 0;

	default:
		if (var_table.has(t.str_val)) {
			return var_table.get(t.str_val);
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

double Calculator::sin() {
	double sub = expression();
	return std::sin(sub);
}

double Calculator::cos() {
	double sub = expression();
	return std::cos(sub);
}

double Calculator::abs() {
	double sub = expression();
	return std::abs(sub);
}

double Calculator::var_declaration()
{
	// handles "let name = [expression]"

	Token t = ts.get_token();
	if (t.type != Token::Types::VAR_NAME)
		throw std::runtime_error("expected variable name in declaration");
	std::string name = t.str_val;

	Token t2 = ts.get_token();
	if (t2.type != Token::Types::OP_EQUAL)
		throw std::runtime_error("expected = after variable name");

	double d = expression();
	var_table.define(name, d);
	return d;
}


double Calculator::print_function() {
	//handles func '['expression']' from [expression] to [expression] step [expression]
	Token exp_tkn = ts.get_token();

	if(exp_tkn.str_val.empty()) 
		throw runtime_error("Expected expression after 'func' keyword");
	
	Token from_tkn = ts.get_token();
	if (from_tkn.type != Token::FUNC_PRINT_FROM) 
		throw runtime_error("Expected 'from' keyword after expression");
	double from = this->expression();

	Token to_tkn = ts.get_token();
	if(to_tkn.type != Token::FUNC_PRINT_TO)
		throw runtime_error("Expected 'to' keyword after 'from'");
	double to = this->expression();

	Token step_tkn = ts.get_token();
	if (step_tkn.type != Token::FUNC_PRINT_STEP)
		throw runtime_error("Expected 'step' keyword after 'to'");
	double step = this->expression();

	if (from > to) swap(from, to);
		
	// remove ; from buffer
	ts.get_token();

	while (from <= to) {
		std::stringstream exp_stream(exp_tkn.str_val + ";");
		Calculator c(exp_stream);
		c.var_table.define("x", from);
		out_stream << "\tF(" << from << ") = " << c.expression() << endl;
		from += step;
	}

	return 0;
}

double Calculator::statement()
{
	Token t = ts.get_token();
	switch (t.type)
	{
	case Token::Types::VAR_DEF:
		return var_declaration();
	case Token::Types::FUNC_DEF:
		return print_function();
	default:
		ts.put_back(t);
		return expression();
	}
}

int Calculator::calculate()
{
	out_stream << std::fixed;
	out_stream << "> ";
	while (in_stream)
		try
		{
			Token t = ts.get_token();
			while (t.type == Token::Types::EXPRESSION_END_FLAG)
				t = ts.get_token();

			if (t.type == Token::Types::EXIT_FLAG)
				return 0;

			ts.put_back(t);

			out_stream << "= " << std::setprecision(prescision) << statement() << endl;
			out_stream << "> " << std::flush;
		}
		catch (exception &e)
		{
			out_stream << "Calculation error: " << e.what() << endl;
			return 1;
		}
		catch (...)
		{
			out_stream << "Unknown error!" << endl;
			return 2;
		}

	return 0;
}

void Calculator::add_const(const string str, double val) {
	this->var_table.define(str, val);
}

void Calculator::set_prescision(int n)
{
	if (n <= 0) throw runtime_error("Prescision can't be lower than 1");
	prescision = n;
}

int Calculator::get_prescision()
{
	return prescision;
}
