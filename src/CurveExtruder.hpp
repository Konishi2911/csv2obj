#ifndef CSV_EXTRUDER_HPP
#define CSV_EXTRUDER_HPP

#include "Curve2D.hpp"
#include "Geometry.hpp"

#include <functional>
#include <string>
#include <stdexcept>

namespace STool {

template<typename T>
std::vector<T> makeSeq(int b, int e, std::function<T(int)> = [](int i) { return i; } );


class CurveExtruder {
public:
    enum Surface { xy, yx, yz, zy, xz, zx };
    static Surface makeSurface(const std::string&);
private:
    Curve2D curve_;
    double offset_ = 0.0;
    Surface surface_;

public:
    // Default condtructor.
    CurveExtruder();

    // Construct with given source curve and a given surface where to place it.
    CurveExtruder(const Curve2D& curve, Surface surf, double offset = 0.0): 
        curve_(curve), 
        surface_(surf),
        offset_(offset) {} 
    CurveExtruder(const Curve2D&& curve, Surface surf, double offset = 0.0): 
        curve_(curve), 
        surface_(surf),
        offset_(offset) {} 


    // set given curve with the surface where to place it.
    void setCurve(const Curve2D&, Surface);

    // Extrude source curve to the given length.
    Geometry extrude(double);

};

}
#endif