#ifndef CT_SEPARATED_VALUES_HPP
#define CT_SEPARATED_VALUES_HPP

#include <vector>
#include <string>
#include <fstream>

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

#endif