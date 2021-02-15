#ifndef CURVE2D_HPP
#define CURVE2D_HPP

#include "SeparatedValues.hpp"
#include "Vector2D.hpp"

#include <string>
#include <vector>

namespace STool {

class Curve2D {
private:
    std::string name_;
   std::vector<Vector2D> verts_; 
   
public:
    // Construct as empty curve.
    Curve2D();

    // Construct curve from given csv.
    Curve2D(const CTool::DoubleSV&, bool close = false);


    // - Accessors

    inline auto name() const { return this->name_; }
    inline auto nVertices() const { return verts_.size(); }
    inline auto verticesList() const { return verts_; }

    
    // - Manipulate Curve

    bool isClosed() const;
    void close();


};

}

#endif