#include "exp_calculator/exp_calculator.h"
#include <sstream>

int main()
{
	Calculator calc(std::cin);
	return calc.calculate();
}
