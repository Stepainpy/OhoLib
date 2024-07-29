/*
convert "Many hands make light work."_to_base64
to      "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu"
*/

#pragma once
#include <cstdint>
#include <string>

namespace oho {

std::string operator""_to_base64(const char* str, size_t n) {
    static const std::string encode_map =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    const size_t padding = (3 - n % 3) % 3;
    const size_t chunk_amount = (n + padding) / 3;
    const size_t data_size = chunk_amount * 4;

    std::string source(str, n);
    std::string data(data_size, '=');

    for (size_t ci = 0; ci < chunk_amount; ci++) {
        // chars from source in chunks. Example "Man"
        //               first char (M)         second char (a)           third char (n)
        uint32_t chunk = source[ci * 3] << 16 | source[ci * 3 + 1] << 8 | source[ci * 3 + 2];
        // i - index of chunk in data
        // j - index of chunk in source
        for (size_t i = 0, j = 1; i < 4; i++, j++) {
            size_t index = chunk >> ((3 - i) * 6);
            if (ci * 3 + j - 1 <= n)
                data[ci * 4 + i] = encode_map[index & 0b111111];
        }
    }

    return data;
}

}