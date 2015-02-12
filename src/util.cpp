// util.cpp --- utility functions used by both gar and lzs parts

#include "util.hpp"

#include <iostream>

uint32_t vec2int32(const std::vector<uint8_t> & data, uint32_t start) {
    uint32_t number = 0;

    for (int i = 0; i < 4; i++) {
        number |= data.at(start + i) << i * 8;
        //std::cerr << std::hex << i << "\n";
        //std::cerr << +data.at(start + i) << "\n";
        //std::cerr << number << std::dec << "\n\n";
    }

    return number;
}

uint16_t vec2int16(const std::vector<uint8_t> & data, uint32_t start) {
    uint16_t number = 0;

    for (int i = 0; i < 2; i++) {
        number |= data.at(start + i) << i * 8;
    }

    return number;
}
