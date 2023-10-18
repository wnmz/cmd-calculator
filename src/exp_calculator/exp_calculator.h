#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <sstream>

#include "token.h"
#include "token_stream.h"
#include "variable_table.h"

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
	double print_function(); // func [expression] from A to B step C
	// return numbers or variable values and handles brackets
	double statement(); // split variable declaration and expression
	double var_declaration(); // let name = [expression]
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