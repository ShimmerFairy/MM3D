// zar_main.cpp --- where the 'zar' program starts

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

#include "zar.hpp"

int main(int argc, char ** argv) {
    if (argc != 3) {
        std::cerr << "Usage:\n";
        std::cerr << "    zar <input file> <output directory>\n";
        return 1;
    }

    std::string infname = argv[1];
    std::string outdir  = argv[2];

    // open archive

    std::ifstream archive(infname, std::ios::binary | std::ios::ate);

    if (archive.fail()) {
        std::cerr << "Could not open \"" << infname << "\".\n";
        return 1;
    }

    const int arcsize = archive.tellg();
    archive.seekg(0);

    // see if it's a gar or lzs file

    char magic[4];
    char arcrawdata[arcsize];
    std::vector<uint8_t> arcdata;

    archive.read(magic, 4);

    archive.seekg(0);
    archive.read(arcrawdata, arcsize);
    archive.close();

    arcdata = std::vector<uint8_t>(arcrawdata, arcrawdata + arcsize);

    if (magic == std::string("ZAR\x01")) {
        zar_ext(arcdata, outdir);
    } else {
        std::cerr << "Not a Zelda Archive. Exiting.\n";
        archive.close();
        return 1;
    }
    return 0;
}
