#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
	std::ifstream input("../y2019d2/input.txt");
	if (!input) {
		return 1;
	}

	std::vector<int> program;
	std::string number;
	while (std::getline(input, number, ',')) {
		program.emplace_back(std::stoi(number));
	}

	input.close();

	// "1202 program alarm" state
	program[1] = 12;
	program[2] = 2;

	for (size_t i = 0; i < program.size(); i += 4) {
		switch (program[i]) {
			case 1:
				program[program[i+3]] = program[program[i+1]] + program[program[i+2]];
				break;
			case 2:
				program[program[i+3]] = program[program[i+1]] * program[program[i+2]];
				break;
			case 99:
				std::cout << "Program finished!" << std::endl;
				std::cout << "Program's 0th element: " << program[0] << std::endl;
				return 0;
			default:
				std::cout << "Invalid opcode!" << std::endl;
				return 1;
		}
	}

	return 0;
}