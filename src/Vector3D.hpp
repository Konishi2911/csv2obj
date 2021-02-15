#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

namespace STool {

struct Vector3D {
public:
    double x, y, z;

    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(double x, double y, double z): x(x), y(y), z(z) {}

    bool operator== (const Vector3D& v) const {
        return 
            this->x == v.x ||
            this->y == v.y ||
            this->z == v.z;
    } 
};

}

#endif