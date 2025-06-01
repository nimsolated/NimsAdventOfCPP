//
// Created by nimsolated on 5/29/2025.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

constexpr int MAX_X = 40000;
constexpr int MAX_Y = 40000;
constexpr int CENTER_X = 20000;
constexpr int CENTER_Y = 20000;

struct Panel {
    char** panel;

    Panel() {
        panel = new char*[MAX_X];
        for (int i = 0; i < MAX_X; i++) {
            panel[i] = new char[MAX_Y];
        }

        for (int i = 0; i < MAX_X; i++) {
            for (int j = 0; j < MAX_Y; j++) {
                panel[i][j] = '.';
            }
        }
    }
    ~Panel() {
        for (int i = 0; i < MAX_X; i++) {
            delete[] panel[i];
        }
        delete[] panel;
    }

    [[nodiscard]] char& at(const int x, const int y) const {
        return panel[x][y];
    }
};

int calcManhattanDistance(const int x1, const int y1, const int x2, const int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int main() {
    std::ifstream input("../y2019d3/input.txt");
    if (!input) { return 1; }

    // Part 1

    auto panel = new Panel();
    panel->at(CENTER_X, CENTER_Y) = 'O';

    std::string wire1, wire2;
    input >> wire1 >> wire2;
    std::istringstream wire1Path(wire1);
    std::istringstream wire2Path(wire2);
    std::string wire1Step, wire2Step;

    // Wire 1 tracing
    int currX = CENTER_X;
    int currY = CENTER_Y;
    while (std::getline(wire1Path, wire1Step, ',')) {
        int steps = std::stoi(wire1Step.substr(1));
        switch (wire1Step[0]) {
            case 'R':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX + i, currY) = '+';
                        break;
                    }
                    panel->at(currX + i, currY) = '1';
                }
                currX += steps;
                break;
            case 'L':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX - i, currY) = '+';
                        break;
                    }
                    panel->at(currX - i, currY) = '1';
                }
                currX -= steps;
                break;
            case 'U':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX, currY + i) = '+';
                        break;
                    }
                    panel->at(currX, currY + i) = '1';
                }
                currY += steps;
                break;
            case 'D':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX, currY - i) = '+';
                        break;
                    }
                    panel->at(currX, currY - i) = '1';
                }
                currY -= steps;
                break;
            default:
                std::cout << "Invalid step in wire 1: " << wire1Step << std::endl;
                delete panel;
                return 1;
        }
    }

    // Wire 2 tracing
    currX = CENTER_X;
    currY = CENTER_Y;
    while (std::getline(wire2Path, wire2Step, ',')) {
        int steps = std::stoi(wire2Step.substr(1));
        switch (wire2Step[0]) {
            case 'R':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX + i, currY) = '+';
                        break;
                    }
                    if (panel->at(currX + i, currY) == '1') {
                        panel->at(currX + i, currY) = 'X';
                        continue;
                    }
                    panel->at(currX + i, currY) = '2';
                }
                currX += steps;
                break;
            case 'L':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX - i, currY) = '+';
                        break;
                    }
                    if (panel->at(currX - i, currY) == '1') {
                        panel->at(currX - i, currY) = 'X';
                        continue;
                    }
                    panel->at(currX - i, currY) = '2';
                }
                currX -= steps;
                break;
            case 'U':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX, currY + i) = '+';
                        break;
                    }
                    if (panel->at(currX, currY + i) == '1') {
                        panel->at(currX, currY + i) = 'X';
                        continue;
                    }
                    panel->at(currX, currY + i) = '2';
                }
                currY += steps;
                break;
            case 'D':
                for (int i = 1; i <= steps; i++) {
                    if (i == steps) {
                        panel->at(currX, currY - i) = '+';
                        break;
                    }
                    if (panel->at(currX, currY - i) == '1') {
                        panel->at(currX, currY - i) = 'X';
                        continue;
                    }
                    panel->at(currX, currY - i) = '2';
                }
                currY -= steps;
                break;
            default:
                std::cout << "Invalid step in wire 2: " << wire2Step << std::endl;
                delete panel;
                return 1;
        }
    }

    int closest = std::numeric_limits<int>::max();
    for (int i = 0; i < MAX_X; i++) {
        for (int j = 0; j < MAX_Y; j++) {
            if (panel->at(i, j) == 'X') {
                closest = std::min(closest, calcManhattanDistance(i, j, CENTER_X, CENTER_Y));
            }
        }
    }

    std::cout << "Closest Intersection: " << closest << std::endl;

    delete panel;
    input.close();
    return 0;
}