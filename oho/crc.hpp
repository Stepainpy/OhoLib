#pragma once
#include <type_traits>
#include <cstdint>
#include <string>

namespace detail {

template <class T, T polynum,
std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
constexpr T crc_table(uint8_t byte) {
    T value = byte;
    for (size_t k = 8; k--;)
        value = (value & 1)
            ? (value >> 1) ^ polynum
            :  value >> 1;
    return value;
}

template <class T, T polynum,
std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
constexpr T crc_alg(const char* data, size_t count) {
    T crc = -1;
    while (count--) crc = (crc >> 8) ^
        crc_table<T, polynum>((crc ^ *data++) & 0xff);
    return ~crc;
}

}

namespace oho {

// ISO 3309 (gzip, PNG and etc.)
constexpr auto crc32(const char* data, size_t count) {
    return ::detail::crc_alg<uint32_t, 0xEDB88320>(data, count);
}
// ECMA version
constexpr auto crc64(const char* data, size_t count) {
    return ::detail::crc_alg<uint64_t, 0xC96C5795D7870F42>(data, count);
}

/* Overloads */

constexpr auto crc32(const std::string& str) {
    return crc32(str.data(), str.size());
}
constexpr auto crc64(const std::string& str) {
    return crc64(str.data(), str.size());
}

constexpr auto crc32(std::string_view str) {
    return crc32(str.data(), str.size());
}
constexpr auto crc64(std::string_view str) {
    return crc64(str.data(), str.size());
}

}