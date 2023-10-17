#include <gtest/gtest.h>
#include "exp_calculator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

TEST(calculator, TestFromFile) {
    fstream test_file;
    test_file.open("../tests/test_expressions.txt", ios::in);
    if (test_file.is_open()) {
        std::string line;

        while (std::getline(test_file, line)) {
            std::istringstream iss(line);
            std::string expression_str;
            double expected_result;

            if (std::getline(iss, expression_str, '|') && iss >> expected_result) {
                std::istringstream input_stream(expression_str + + ";");
                std::ostringstream out_stream("");

                Calculator calc(input_stream, out_stream);
                calc.calculate();

                string output = out_stream.str();

                std::ostringstream oss;
                oss << std::fixed << std::setprecision(calc.get_prescision()) << expected_result;
                std::string valueAsString = oss.str();
                string expected = "> = " + valueAsString + "\n> ";

                ASSERT_EQ(output, expected);
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
