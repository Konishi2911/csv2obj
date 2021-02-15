#ifndef ARGS_PERSER_HPP
#define ARGS_PERSER_HPP

#include <iostream>
#include <iomanip>

#include <vector>
#include <map>
#include <string>
#include <functional>

#include <stdexcept>

// namespace of general utilities.
namespace BasicUtl {

class ArgsParser {
private:
    
    // Definition of option.
    struct Opt {
    public:
        char shortStyl;
        std::string longStyl;
        std::string description;

        bool hasValue;

        Opt(): shortStyl(), longStyl(), description(), hasValue(false) {}
        Opt(char s, const std::string& l, const std::string& desc, bool hasValue):
            shortStyl(s), 
            longStyl(l), 
            description(desc), 
            hasValue(hasValue)
        {}
        Opt(const Opt& opt): 
            shortStyl(opt.shortStyl), 
            longStyl(opt.longStyl), 
            description(opt.description),
            hasValue(opt.hasValue)
        {}

        bool operator== (const Opt& o) {
            return 
                this->shortStyl == o.shortStyl && 
                this->longStyl == o.longStyl &&
                this->description == o.description &&
                this->hasValue == o.hasValue;
        }
    };

    std::vector<std::string> usages_;
    std::vector<Opt> optDict_;
    std::vector<std::pair<Opt, std::string>> optValues_;
    std::vector<std::string> values_;

    // Returns true if optionDict contains given option, false it doesn't.
    // If optionDict contains given option, matched option object will set to second arg.
    bool isRegisteredOpt_(std::string, Opt&) const;

    std::string searchOptValue_(const Opt&) const;


    // show help
    void showHelp() const;

public:
    // Sets a usage description. If there are multiple usage, set them with calling this method multiple time.
    void setUsage(std::string);

    // Sets a definition of option.
    void setOption(char s, const std::string& l, const std::string& desc, bool hasValue = false) {
        this->optDict_.emplace_back(s, l, desc, hasValue);
    }

    std::vector<std::string> getArgs() const { return values_; }

    // Returns a given type value corresponding to given option specifier.
    template<typename VT> VT getValue(const std::string&) const;
    template<typename VT> VT getValue(const std::string&, std::function<VT(const std::string&)>) const;

    // Returns whether the given option exists.
    bool exists(const std::string&) const;

    // Parses given command line arguments.
    void parse(int argc, char* argv[]);
};


// - Implementation

void ArgsParser::setUsage(std::string usage) {
    this->usages_.push_back(usage);
}
void ArgsParser::showHelp() const {
    for (auto usage: this->usages_) {
        std::cout << "\033[1mUsage: \033[m" << usage << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Options are shown in below." << std::endl;
    for (auto opt: this->optDict_) {
        std::cout << " " << std::setw(10) << std::left << std::string("-") + opt.shortStyl << ": "
            << opt.description << std::endl;
    }
}

bool ArgsParser::exists(const std::string& optstr) const {
    for (auto [opt, value]: this->optValues_) {
        if (optstr == std::string(1, opt.shortStyl) || optstr == opt.longStyl) return true;
    }
    return false;
}

template<>
int ArgsParser::getValue( const std::string& optstr ) const {
    auto tOpt = Opt();
    if (isRegisteredOpt_(optstr, tOpt) && exists(optstr)) return std::stoi(searchOptValue_(tOpt));
    else throw std::runtime_error("Unknown option -" + optstr + " has been passed.");
}

template<>
double ArgsParser::getValue( const std::string& optstr ) const {
    auto tOpt = Opt();
    if (isRegisteredOpt_(optstr, tOpt) && exists(optstr)) return std::stod(searchOptValue_(tOpt));
    else throw std::runtime_error("Unknown option -" + optstr + " has been passed.");
}

template<>
std::string ArgsParser::getValue(const std::string& optstr) const {
    auto tOpt = Opt();
    if (isRegisteredOpt_(optstr, tOpt) && exists(optstr)) return searchOptValue_(tOpt);
    else throw std::runtime_error("Unknown option -" + optstr + " has been passed.");
}

template<typename VT> 
VT ArgsParser::getValue(const std::string& optstr, std::function<VT(const std::string&)> conv) const {
    auto tOpt = Opt();
    if (isRegisteredOpt_(optstr, tOpt) && exists(optstr)) return conv(searchOptValue_(tOpt));
    else throw std::runtime_error("Unknown option -" + optstr + " has been passed.");
}

std::string ArgsParser::searchOptValue_(const Opt& optObj) const {
    for (auto ov: this->optValues_) {
        if (ov.first == optObj) return ov.second;
    }
    return std::string();
}

bool ArgsParser::isRegisteredOpt_(std::string option, Opt& hitOpt) const {
    for (auto opt: this->optDict_) {
        if (option == std::string(1, opt.shortStyl) || option == opt.longStyl) {
            hitOpt = opt;
            return true;
        }
    }
    return false;
}

void ArgsParser::parse(int argc, char* argv[]) {
    for (auto i = 1; i < argc; ++i) {
        auto arg = std::string(argv[i]);
        auto opt = Opt();

        if (*arg.begin() == '-') {
            // Erase specifier of short style option.
            arg.erase(arg.begin());

            if (arg == "h") this->showHelp();
            else if (isRegisteredOpt_(arg, opt)) {
                if (opt.hasValue) 
                    this->optValues_.emplace_back(opt, std::string(argv[++i]));
                else 
                    this->optValues_.emplace_back(opt, std::string());
            } else {
                throw std::runtime_error("Unknown option -" + arg + " has specified.");
            }
        } else {
            values_.push_back(arg);
        }
    }
}

}
#endif