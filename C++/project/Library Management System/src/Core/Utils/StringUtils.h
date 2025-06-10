#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <algorithm>
#include <cctype>

namespace util {

inline std::string trim(const std::string& s) {
    auto begin = s.find_first_not_of(" \t\n\r");
    if (begin == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\n\r");
    return s.substr(begin, end - begin + 1);
}

inline std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

} // namespace util

#endif // STRING_UTILS_H
