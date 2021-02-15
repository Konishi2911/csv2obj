#include "SeparatedValues.hpp"
#include "CurveExtruder.hpp"

#include <iostream>
#include <fstream>

int main() {
    auto csvPath = std::filesystem::path("/Users/koheikonishi/Documents/GeneralUtilities/csv2obj/test/test.csv");
    auto csv = CTool::DoubleSV(csvPath);

    auto extruder = STool::CurveExtruder(STool::Curve2D(csv), STool::CurveExtruder::Surface::xy);
    auto obj = extruder.extrude(1);
    std::cout << obj.makeStr() << std::endl;
}