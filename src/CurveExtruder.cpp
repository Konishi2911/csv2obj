#include "CurveExtruder.hpp"

STool::CurveExtruder::Surface
STool::CurveExtruder::makeSurface(const std::string& surfStr) {
    if (surfStr == "xy") return Surface::xy;
    else if (surfStr == "yx") return Surface::yx;
    else if (surfStr == "yz") return Surface::yz;
    else if (surfStr == "zy") return Surface::zy;
    else if (surfStr == "xz") return Surface::xz;
    else if (surfStr == "zx") return Surface::zx;
    else throw std::invalid_argument("Unknown specifier: " + surfStr);
}

STool::Geometry STool::CurveExtruder::extrude(double length) {
    auto vertices = std::vector<Vector3D>();
    auto faces = std::vector<std::vector<int>>();

    for (auto point: curve_.verticesList()) {
        switch (this->surface_) {
            case xy:
            vertices.emplace_back(point.x, point.y, 0.0);
            vertices.emplace_back(point.x, point.y, length);
            break;

            case yx:
            vertices.emplace_back(point.y, point.x, 0.0);
            vertices.emplace_back(point.y, point.x, length);
            break;

            case yz:
            vertices.emplace_back(0.0, point.x, point.y);
            vertices.emplace_back(length, point.x, point.y);
            break;

            case zy:
            vertices.emplace_back(0.0, point.y, point.x);
            vertices.emplace_back(length, point.y, point.x);
            break;

            case zx:
            vertices.emplace_back(point.y, 0.0, point.x);
            vertices.emplace_back(point.y, length, point.x);
            break;

            case xz:
            vertices.emplace_back(point.x, 0.0, point.y);
            vertices.emplace_back(point.x, length, point.y);
            break;
        }
    }

    auto n = this->curve_.nVertices();
    auto sideFace1 = makeSeq<int>(0, n, [](int i) { return 2 * i + 1; });
    auto sideFace2 = makeSeq<int>(0, n, [](int i) { return 2 * i + 2; });

    faces.push_back(sideFace1);
    faces.push_back(sideFace2);
    for (auto k = 1; k < 2*n-2; k += 2) {
        faces.push_back( { k, k+1, k+3, k+2 } );
    }

    Geometry geometry;
    geometry.name(this->curve_.name());
    geometry.vList(vertices);
    geometry.fIDList(faces);

    return geometry;
}

template<typename T>
std::vector<T> STool::makeSeq(int b, int s, std::function<T(int)> gen) {
    auto vec = std::vector<T>();
    for (int i = b; i < s; ++i) {
        vec.push_back(gen(i));
    }
    return vec;
}