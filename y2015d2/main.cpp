//
// Created by nimsolated on 6/8/2025.
//
#include <iostream>
#include <fstream>
#include <string>

struct Box {
    int length;
    int width;
    int height;

    Box(const int l, const int w, const int h) : length(l), width(w), height(h) {}
};

// Box object from a string
Box strToBox(const std::string& str) {
    const size_t firstX = str.find('x');
    const size_t secondX = str.find('x', firstX + 1);

    const int l = std::stoi(str.substr(0, firstX));
    const int w = std::stoi(str.substr(firstX + 1, secondX - firstX - 1));
    const int h = std::stoi(str.substr(secondX + 1));

    const Box box(l, w, h);
    return box;
}

int areaOfSmallestSide(const Box& box) {
    return std::min(box.length * box.width, std::min(box.width * box.height, box.height * box.length));
}

int calcBoxSqft(const Box& box) {
    return 2 * ((box.length * box.width) + (box.width * box.height) + (box.length * box.height));
}

int perimeterOfSmallestFace(const Box& box) {
    const int smallest = std::min(box.length, std::min(box.width, box.height));
    if (smallest == box.length) {
        return 2 * (box.length + std::min(box.width, box.height));
    }
    if (smallest == box.width) {
        return 2 * (box.width + std::min(box.length, box.height));
    }
    return 2 * (box.height + std::min(box.length, box.width));
}

int calcRibbonFt(const Box& box) {
    return (box.length * box.width * box.height) + perimeterOfSmallestFace(box);
}

int main() {
    std::ifstream input("../y2015d2/input.txt");
    if (!input) { return 1; }

    // Part 1

    std::string boxDimensions;
    int totalSqft = 0;
    int totalRibbonFt = 0;
    while (input >> boxDimensions) {
        Box box = strToBox(boxDimensions);
        totalSqft += (calcBoxSqft(box) + areaOfSmallestSide(box));
        // Part 2
        totalRibbonFt += calcRibbonFt(box);
    }

    std::cout << "Total Sqft of Wrapping Paper: " << totalSqft << std::endl;
    std::cout << "Total Feet of Ribbon: " << totalRibbonFt << std::endl;

    return 0;
}