// Взято с https://stackoverflow.com/a/7666577

#pragma once
#include <string>

namespace oho {

namespace literals {

constexpr unsigned long operator""_hash(const char* str, size_t size) {
    auto hash = 5381ul;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

};

unsigned long hash(const std::string& stdstr) {
    const char* str = stdstr.c_str();
    auto hash = 5381ul;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

unsigned long hash(const char* str) {
    auto hash = 5381ul;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

};