# CMD Calculator
Command line math expressions calculator inspired by Bjarne Stroustrup's book "Programming: Principles and Practice"

## How to Build?
1. Install CMake.
2. Clone the repository: `git clone https://github.com/wnmz/cmd-calculator`
3. Navigate to the project directory: `cd ./cmd-calculator`
4. Run CMake to configure the project build: `cmake -B ./build`
5. In the build directory, you'll find either a working Makefile or a Visual Studio project.

   - For Makefile, run the following command to execute or build:
     - `make run` to run
     - `make` to build

   - For Visual Studio, open ExpCalculator.sln and build the subproject named main.
6. Locate the main binary file in the /build/output folder and run it.

## Abilities
- Operators:
  - Unary: +, -
  - Binary: +, -, ^ (power, e.g., a^b)
  - Brackets ()
- Constants: e, pi
- Functions: abs, sin, cos
- User-defined variables: 
  - Example: `let a = sin(3)`
- Nested expressions support, such as: `(5-3)^(1-(e^2 - sin(pi^2))`
- Print function in range from A to B with step C
  - Example: `func [2x^(-4)+sin(x^2)] from -(5^1) to 5^4 step 0.1`

## Usage
Simply write your statement, ending each line with a semicolon (;), and press Enter.

## TODO:
1. Rewrite using flexible OOP patterns 🙏
