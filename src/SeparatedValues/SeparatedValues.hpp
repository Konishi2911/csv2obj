#ifndef CT_SEPARATED_VALUES_HPP
#define CT_SEPARATED_VALUES_HPP

#include "StringSplitter.hpp"
#include "FileFormatError.hpp"

#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace CTool {

template<typename Type> class SeparatedValues;

// Declearation of aliases.
using IntSV = SeparatedValues<int>;
using DoubleSV = SeparatedValues<double>;


template<typename Type>
class SeparatedValues {
private:
    // The name of this SV.
    std::string name_;


    // Number of rows.
    int nRows_;

    // Number of columns.
    int nCols_;

    // The Headings for columns.
    std::vector<std::string> headers_;

    // The collection of SV records.
    std::vector<std::vector<Type>> records_;


    // Delimiter
    std::string delimiter_ = ",";

    // Line feed code
    std::string lfCode_ = "\r\n";

public:
    // - Constructors

    // Construct from a file loaded from given file path.
    SeparatedValues(const std::filesystem::path&, bool withHeader = false);

    // Construct from a part of given other separated value object.
    SeparatedValues(const SeparatedValues<Type>&, std::pair<int, int>, std::pair<int, int>);

    // Construct from given vector collection.
    SeparatedValues(const std::vector<std::vector<Type>>&);


    // - Accessors
    
    // Name of this Separated Values.
    const std::string& name() const;
    void name(const std::string& name);

    int nRows() const;
    int nCols() const;

    inline const std::vector<Type>& lineAt(int i) const { return this->records_[i]; }
    inline const Type& at(int i, int j) const { return this->records_[i][j]; }


    // - Member Functions

    bool withHeader() const;

    // Export separated values to file to given file path.
    void makeFile(const std::filesystem::path&);

    // for debug;
    void printAllRecords();

private:
    // - Private Member Functions

    // 
    std::vector<std::vector<Type>> makeRecords(const std::vector<std::vector<std::string>>&);

    // Converts string data to specified type.
    Type convert_(const std::string&);

    // Represent separated value with string.
    std::string makeString_();
};

}


// - Comstructors

template<typename Type>
CTool::SeparatedValues<Type>::SeparatedValues(
    const std::filesystem::path& filePath,
    bool withHeader
) : name_(filePath.stem())
{
    std::ifstream ifs(filePath, std::ios::in);
    if (ifs.is_open()) {
        auto splitter = StringSplitter(delimiter_);
        auto dataStr = std::string(
            std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>()
        );

        if (dataStr.empty())  throw FileFormatError("Loaded file was empty.");

        auto dataStrVec = splitter.split(dataStr);

        if (withHeader) {
            this->headers_ = *dataStrVec.begin();
            dataStrVec.erase(dataStrVec.begin());
        }

        this-> nRows_ = dataStrVec.size();
        this-> nCols_ = dataStrVec[0].size();
        this->records_ = makeRecords(dataStrVec);
    }
}

template<typename Type>
CTool::SeparatedValues<Type>::SeparatedValues(
    const SeparatedValues<Type>& sv,
    std::pair<int, int> rowRange,
    std::pair<int, int> colRange
) : name_(sv.name_)    
{

    // Check Initial conditions ( Bound check ).
    if (rowRange.first < 0 || rowRange.first >= sv.nRows_)  
        throw std::out_of_range("Given lower bound of row was out of range of the source object.");
    if (rowRange.second < 0 || rowRange.second >= sv.nRows_)  
        throw std::out_of_range("Given upper bound of row was out of range of the source object.");
    if (colRange.first < 0 || colRange.first >= sv.nCols_)  
        throw std::out_of_range("Given lower bound of column was out of range of the source object.");
    if (colRange.second < 0 || colRange.second >= sv.nCols_)  
        throw std::out_of_range("Given upper bound of column was out of range of the source object.");

    auto rec = sv.records_;
    auto vec = std::vector<std::vector<Type>>();
    for (int i = rowRange.first; i <= rowRange.second; ++i) {
        auto v = std::vector<Type>();
        for (int j = colRange.first; j <= colRange.second; ++j) {
            v.push_back(rec[i][j]);
        }
        vec.push_back(v);
    }

    this->nRows_ = vec.size();
    this->nCols_ = vec[0].size();
    this->records_ = vec;
}

template<typename Type>
CTool::SeparatedValues<Type>::SeparatedValues(const std::vector<std::vector<Type>>& values): 
    records_(values)
{
}


// - Accessors

template<typename Type>
const std::string& CTool::SeparatedValues<Type>::name() const {
    return this->name_;
}
template<typename Type>
void CTool::SeparatedValues<Type>::name(const std::string& name) {
    this->name_ = name;
}


template<typename Type>
int CTool::SeparatedValues<Type>::nRows() const {
    return this->nRows_;
}

template<typename Type>
int CTool::SeparatedValues<Type>::nCols() const {
    return this->nCols_;
}


// - Mamber Functions

template<typename Type>
bool CTool::SeparatedValues<Type>::withHeader() const {
    return !this->headers_.empty();
}

template<typename Type>
void CTool::SeparatedValues<Type>::makeFile(const std::filesystem::path& filePath) {
    
    auto ofs = std::ofstream(filePath);
    if (ofs.is_open()) {
        ofs << makeString_();

        ofs.close();
    }
}

template<typename Type>
void CTool::SeparatedValues<Type>::printAllRecords() {
    std::cout << makeString_() << std::endl;
}

// - Private Member Functions

template<typename Type>
std::vector<std::vector<Type>>
CTool::SeparatedValues<Type>::makeRecords(
    const std::vector<std::vector<std::string>>& sVec
) {
    auto vec = std::vector<std::vector<Type>>();

    for (auto row: sVec) {
        auto rowVec = std::vector<Type>();
        for (auto rec: row) {
            rowVec.push_back(
                convert_(rec)
            );
        }
        vec.push_back(rowVec);
    }

    return vec;
}

template<typename Type>
std::string CTool::SeparatedValues<Type>::makeString_() {
    auto str = std::string();

    if (!this->headers_.empty()) {
        for (auto i = 0; i < nCols_ - 1; ++i) {
            str += headers_[i] + delimiter_;
        }
        str += headers_[nCols_ - 1] + lfCode_;
    }

    if (!this->records_.empty()) {
        for (auto i = 0; i < nRows_; ++i) {
            for (auto j = 0; j < nCols_ - 1; ++j) {
                str += std::to_string(records_[i][j]) + delimiter_;
            }
            str += std::to_string(records_[i][nCols_ - 1]) + lfCode_;
        }
    }

    return str;
}

#endif