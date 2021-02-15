#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

namespace STool {

struct Vector2D {
public:
    double x, y;

    Vector2D(): x(0), y(0) {}
    Vector2D(double x, double y): x(x), y(y) {}

    bool operator== (const Vector2D& v) const {
        return 
            this->x == v.x ||
            this->y == v.y;
    } 
};

}

#endif