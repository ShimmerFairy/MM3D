// lzs_main.cpp --- where the 'lzs' program starts

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

#include "lzs.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
    if (argc != 3) {
        std::cerr << "Usage:\n";
        std::cerr << "    lzs <input file> <output file>\n";
        return 1;
    }

    std::string infname  = argv[1];
    std::string outfname = argv[2];

    // open file

    std::ifstream infile(infname, std::ios::binary | std::ios::ate);

    if (infile.fail()) {
        std::cerr << "Could not open \"" << infname << "\".\n";
        return 1;
    }

    const int filesize = infile.tellg();
    infile.seekg(0);

    // see if it's an LZS file

    char magic[4];
    char filerawdata[filesize];
    std::vector<uint8_t> filedata;

    infile.read(magic, 4);

    infile.seekg(0);
    infile.read(filerawdata, filesize);
    infile.close();
    filedata = std::vector<uint8_t>(filerawdata, filerawdata + filesize);

    if (magic == std::string("LzS\x01")) {
        filedata = lzs_dec(filedata);
        writeFile(outfname, "", (char*)filedata.data(), filedata.size());
    } else {
        std::cerr << "Not an LzS file.\n";
        return 1;
    }

    return 0;
}
