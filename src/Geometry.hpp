#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "Vector3D.hpp"

#include <filesystem>
#include <vector>
#include <string>

// Shape Tools
namespace STool {

class Geometry {
private:
    const std::string extension_ = ".obj";

    std::string name_;
    std::vector<Vector3D> vertices_;
    std::vector<std::vector<int>> faceIDs_;

public:
    Geometry();

    inline auto name() const { return this->name_; }
    inline auto vList() const { return this->vertices_; }
    inline auto fIDList() const { return this->faceIDs_; }

    inline void name(const std::string& name) { this->name_ = name; }
    inline void vList(const std::vector<Vector3D>& v) { this->vertices_ = v; }
    inline void fIDList(const std::vector<std::vector<int>>& f) { this->faceIDs_ = f; }

    std::string makeStr() const;
    void output(const std::filesystem::path&);
};

}

#endif