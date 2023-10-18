#include "variable_table.h"

void VariableTable::define(std::string name, double var) {
	vars[name] = var;
}

double VariableTable::get(std::string name) {
	return vars[name];
}

bool VariableTable::has(std::string name) {
	return vars.find(name) != vars.end();
}