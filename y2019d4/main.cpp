//
// Created by nimsolated on 6/1/2025.
//
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream input("../y2019d4/input.txt");
    if (!input) { return 1; }

    // Part 1 and 2

    std::string range;
    input >> range;
    const int min = std::stoi(range.substr(0, range.find('-')));
    const int max = std::stoi(range.substr(range.find('-') + 1));
    input.close();

    std::vector<std::string> possiblePart1Passwords;
    std::vector<std::string> possiblePart2Passwords;
    for (int i = min; i <= max; i++) {
        bool hasDouble = false;
        bool isAscending = true;
        bool hasExactDouble = false;
        std::string pass = std::to_string(i);
        for (size_t j = 0; j < pass.size() - 1; j++) {
            if (pass[j] > pass[j + 1]) {
                isAscending = false;
                break;
            }
            if (pass[j] == pass[j + 1]) {
                hasDouble = true;

                bool isLargerGroup = false;
                if (j > 0 && pass[j - 1] == pass[j]) {
                    isLargerGroup = true;
                }
                if (j + 2 < pass.size() && pass[j + 1] == pass[j + 2]) {
                    isLargerGroup = true;
                }
                if (!isLargerGroup) {
                    hasExactDouble = true;
                }
            }
        }
        if (isAscending && hasDouble) {
            possiblePart1Passwords.emplace_back(pass);
        }
        if (isAscending && hasExactDouble) {
            possiblePart2Passwords.emplace_back(pass);
        }
    }

    std::cout << "Number of possible passwords (part 1): " << possiblePart1Passwords.size() << std::endl;
    std::cout << "Number of possible passwords (part 2): " << possiblePart2Passwords.size() << std::endl;

    return 0;
}
