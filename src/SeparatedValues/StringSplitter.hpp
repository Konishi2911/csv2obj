#ifndef CT_STRING_SPLITTER_HPP
#define CT_STRING_SPLITTER_HPP

#include <vector>
#include <string>

namespace CTool {

class StringSplitter {
private:
    // Delimiter
    std::string delimiter_;

    // Line Feed Code
    const std::string lf_dos = "\r\n";
    const std::string lf_mac = "\r";
    const std::string lf_unix = "\n";

public:
    // - Constructors

    // default constructor
    StringSplitter();

    // Construct StringSplitter with given delimiter and line feed code.
    StringSplitter(const std::string&);


    // - Member Functions

    // Split given source string with set delimiter and line feed code.
    std::vector<std::vector<std::string>> split(const std::string&);

private:
    // - Private Member Functions

    // Split with line feed code.
    std::vector<std::string> splitWithLFCode(const std::string&);

    // Split source string by given delimiter.
    std::vector<std::string> splitByDelimiter(const std::string&, const std::string&);

};

}

#endif