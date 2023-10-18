#pragma once
#include <string>
#include <unordered_map>

class VariableTable {
private:
	std::unordered_map<std::string, double> vars;
public:
	void define(std::string name, double var);
	double get(std::string name);
	bool has(std::string name);
};