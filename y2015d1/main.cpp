//
// Created by nimsolated on 6/8/2025.
//
#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("../y2015d1/input.txt");
    if (!input) { return 1; }

    // part 1

    std::string directions;
    input >> directions;
    input.close();
    int floor = 0;
    for (size_t i = 0; i < directions.size(); i++) {
        if (directions[i] == '(') {
            floor++;
        } else if (directions[i] == ')') {
            floor--;
            // part 2
            if (floor == -1) {
                std::cout << "Entered Basement at Position: " << i + 1 << std::endl;
            }
        }
    }

    std::cout << "Floor Reached After Instructions: " << floor << std::endl;

    return 0;
}