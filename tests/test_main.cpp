#include <gtest/gtest.h>
#include "exp_calculator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

TEST(calculator, TestFromFile) {
    Calculator calc = Calculator();
    fstream test_file;
    test_file.open("../tests/test_expressions.txt", ios::in);
    if (test_file.is_open()) {
        std::string line;

        while (std::getline(test_file, line)) {
            std::istringstream iss(line);
            std::string expression_str;
            double result;

            if (std::getline(iss, expression_str, ';') && iss >> result) {
                std::istringstream input_stream(expression_str + + ";q");

                std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

                std::stringstream captured_output;
                std::streambuf* old_cout = std::cout.rdbuf(captured_output.rdbuf());

                calc.calculate();

                std::cin.rdbuf(old_cin);
                std::cout.rdbuf(old_cout);

                std::ostringstream expected_output_stream;
                expected_output_stream << "> = " 
                    << std::fixed << std::setprecision(4)
                    << result << "\n> ";
                std::string expected_output = expected_output_stream.str();
                EXPECT_EQ(captured_output.str(), expected_output);
            } else {
                std::cerr << "Error: Invalid line format: " << line << std::endl;
            }
        }
        test_file.close();
    } else {
        FAIL() << "Unable to open file: test_expressions.txt" << endl;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
