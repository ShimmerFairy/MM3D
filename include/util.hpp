// util.hpp --- include for utility functions

#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <cstdint>
#include <string>

uint32_t vec2int32(const std::vector<uint8_t> & data, uint32_t start);
uint16_t vec2int16(const std::vector<uint8_t> & data, uint32_t start);
void writeFile(std::string outdir, std::string filename, char * filedata, uint32_t filesize);

#endif // UTIL_HPP
