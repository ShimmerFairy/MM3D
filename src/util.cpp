// util.cpp --- utility functions used by both gar and lzs parts

#include "util.hpp"

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

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

void writeFile(std::string outdir, std::string filename, char * filedata, uint32_t filesize) {
    boost::filesystem::path outpath;
    std::ofstream outfile;

    outpath = outdir;
    outpath = boost::filesystem::absolute(outpath);

    outfile.open((outpath / filename).string(), std::ios::binary);
    outfile.write(filedata, filesize);
    outfile.close();
}
