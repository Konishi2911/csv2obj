#include "Curve2D.hpp"

STool::Curve2D::Curve2D(const CTool::DoubleSV& csv, bool close):
    verts_(),
    name_(csv.name())
{
    auto nPoints = csv.nRows();
    for (auto i = 0; i < nPoints; ++i) {
        this->verts_.emplace_back(csv.lineAt(i)[0], csv.lineAt(i)[1]);
    }

    if (close) this->close();
}


// - Manipulate curve

bool STool::Curve2D::isClosed() const {
    return *this->verts_.begin() == *this->verts_.end();
}

void STool::Curve2D::close() {
    if (!this->isClosed()) {
        this->verts_.push_back(*this->verts_.begin());
    }
}