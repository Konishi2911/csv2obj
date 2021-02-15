#include "Geometry.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

STool::Geometry::Geometry(): 
    name_(),
    vertices_(),
    faceIDs_()
{}

std::string STool::Geometry::makeStr() const {
    std::stringstream ss;

    // make vertices list. 
    for (auto point: this->vertices_) {
        ss << "v " << point.x << " " << point.y << " " << point.z << std::endl;
    }

    // make face data.
    for (auto vertList: this->faceIDs_) {
        ss << "f ";
        auto last = vertList.size() - 1;
        for (auto i = 0; i < last; ++i) {
            ss << vertList[i] << " ";
        }
        ss << vertList[last] << std::endl;
    }
    return ss.str();
}

void STool::Geometry::output(const std::filesystem::path& targetDir) {
    auto filepath = std::filesystem::path(targetDir).append(this->name_ + this->extension_); 
    auto ofs = std::ofstream(filepath);

    ofs << makeStr();
    ofs.close();

    std::cout << "place obj file to: " << filepath << std::endl;
    
}