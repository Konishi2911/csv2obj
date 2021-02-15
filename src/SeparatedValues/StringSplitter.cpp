#include "StringSplitter.hpp"

// - Constructors

CTool::StringSplitter::StringSplitter():
    delimiter_(",")
{}

CTool::StringSplitter::StringSplitter(const std::string& del):
    delimiter_(del)
{}


// - Member Functions

std::vector<std::vector<std::string>> 
CTool::StringSplitter::split(const std::string& source) {
    auto lineVec = splitWithLFCode(source);

    auto elements = std::vector<std::vector<std::string>>();
    for (auto str: lineVec) {
        elements.push_back(
            splitByDelimiter(str, this->delimiter_)
        );
    }
    return elements;
}

std::vector<std::string>
CTool::StringSplitter::splitWithLFCode(const std::string& source) {
    if (source.find(this->lf_dos) != std::string::npos) {
        return splitByDelimiter(source, lf_dos);
    } 
    else if (source.find(this->lf_mac) != std::string::npos) {
        return splitByDelimiter(source, lf_mac);
    } 
    else if (source.find(this->lf_unix) != std::string::npos) {
        return splitByDelimiter(source, lf_unix);
    }
}

std::vector<std::string> 
CTool::StringSplitter::splitByDelimiter(const std::string& source, const std::string& del) {

    std::vector<std::string> vec;

    auto prevPos = std::string::size_type(0);
    while(1) {
        auto pos = source.find(del, prevPos);
        if (pos == std::string::npos) {
            // Ignore empty element.
            if (source.size() == prevPos) break;

            vec.emplace_back(source.begin() + prevPos, source.end());
            break;
        } else {
            vec.emplace_back(source.begin() + prevPos, source.begin() + pos);
        }
        prevPos = pos + del.size();
    }

    return vec;
}   
