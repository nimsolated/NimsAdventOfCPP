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
	const std::vector<int> programBackup = program;

	// Part 1
	// "1202 program alarm" state

	program[1] = 12;
	program[2] = 2;

	for (size_t i = 0; i < program.size(); i += 4) {
		if (program[i] == 99) {
			std::cout << "Program finished!" << std::endl;
			std::cout << "Program's 0th element: " << program[0] << std::endl;
			break;
		}

		switch (program[i]) {
			case 1:
				program[program[i+3]] = program[program[i+1]] + program[program[i+2]];
				break;
			case 2:
				program[program[i+3]] = program[program[i+1]] * program[program[i+2]];
				break;
			default:
				std::cout << "Invalid opcode!" << std::endl;
				return 1;
		}
	}

	program = programBackup;

	// Part 2

	int noun = 0;
	int verb = 0;
	for (noun = 0; noun < 100; noun++) {
		for (verb = 0; verb < 100; verb++) {
			program[1] = noun;
			program[2] = verb;

			for (size_t i = 0; i < program.size(); i += 4) {
				const int opcode = program[i];

				if (opcode == 99) {
					break;
				}

				const int param1 = program[i+1];
				const int param2 = program[i+2];
				const int output = program[i+3];

				switch (opcode) {
					case 1:
						program[output] = program[param1] + program[param2];
						break;
					case 2:
						program[output] = program[param1] * program[param2];
						break;
					default:
						std::cout << "Invalid opcode!" << std::endl;
						return 1;
				}
			}

			if (program[0] == 19690720) {
				break;
			}

			program = programBackup;
		}

		if (program[0] == 19690720) {
			break;
		}
	}

	std::cout << "Program state that produce 19690720: " << (100 * noun + verb) << std::endl;

	return 0;
}