// Взято с https://stackoverflow.com/a/217605

#pragma once
#include <string>
#include <algorithm>
#include <locale>

namespace oho {

// trim from start (in place)
inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

// copy versions
inline std::string ltrimc(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (in place)
inline std::string rtrimc(std::string s) {
    rtrim(s);
    return s;
}

inline std::string trimc(std::string s) {
    ltrim(s);
    rtrim(s);
    return s;
}

}