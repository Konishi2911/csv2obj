#ifndef CT_FILE_FORMAT_EXCEPTION_HPP
#define CT_FILE_FORMAT_EXCEPTION_HPP

#include <stdexcept>

namespace CTool {

class FileFormatError: public std::runtime_error {
    using std::runtime_error::runtime_error;
};

}

#endif