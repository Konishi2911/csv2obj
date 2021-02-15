#include "SeparatedValuesI.hpp"

#include <charconv>

template<>
int CTool::SeparatedValues<int>::convert_(const std::string& str) {
    return std::stoi(str);
}

template<>
double CTool::SeparatedValues<double>::convert_(const std::string& str) {
    return std::stod(str);
}

namespace CTool {
    template class SeparatedValues<int>;
    template class SeparatedValues<double>;
}