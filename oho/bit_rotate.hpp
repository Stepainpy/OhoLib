#pragma once
#include <cstddef>  // size_t
#include <concepts> // unsigned_integral
#include <limits>   // numeric_limits

namespace oho {

template <class Int> requires std::unsigned_integral<Int>
Int rotl(Int n, size_t count) {
    return (n << count) | (n >> (std::numeric_limits<Int>::digits - count));
}

template <class Int> requires std::unsigned_integral<Int>
Int rotr(Int n, size_t count) {
    return (n >> count) | (n << (std::numeric_limits<Int>::digits - count));
}

}