// util.hpp --- include for utility functions

#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <cstdint>

uint32_t vec2int32(const std::vector<uint8_t> & data, uint32_t start);
uint16_t vec2int16(const std::vector<uint8_t> & data, uint32_t start);

#endif // UTIL_HPP
