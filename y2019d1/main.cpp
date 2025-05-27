#include <iostream>
#include <fstream>
#include <vector>

static long calcFuelFromMass(const long mass) {
    return mass / 3 - 2;
}

int main() {
    std::ifstream input("../y2019d1/input.txt");
    if (!input) {
        return 1;
    }

    // Part 1

    long mass = 0;
    std::vector<long> fuelReqs;
    long preTotalFuelReq = 0;
    while (input >> mass) {
        fuelReqs.emplace_back(calcFuelFromMass(mass));
    }
    input.close();

    for (const long req : fuelReqs) {
        preTotalFuelReq += req;
    }
    std::cout << "Total Fuel Requirements: " << preTotalFuelReq << std::endl;

    // Part 2

    long totalFuelReq = 0;
    for (long& req : fuelReqs) {
        totalFuelReq += req;
        while (calcFuelFromMass(req) > 0) {
            totalFuelReq += calcFuelFromMass(req);
            req = calcFuelFromMass(req);
        }
    }
    std::cout << "Total Fuel Requirements (taking into account the mass of added fuel): "
        << totalFuelReq << std::endl;

    return 0;
}