// lzs.cpp --- decompresses .gar.lzs files

#include "lzs.hpp"
#include "util.hpp"

#include <iostream>
#include <cstdlib>
#include <array>

std::vector<uint8_t> lzs_dec(std::vector<uint8_t> arcdata) {
    uint32_t decsize = vec2int32(arcdata, 0x8);
    uint32_t cmpsize = vec2int32(arcdata, 0xC);

    std::vector<uint8_t> outdata;

    if (arcdata.size() != cmpsize + 0x10) {
        std::cerr << "Size mismatch: got " << arcdata.size() << "bytes, expected " << cmpsize + 0x10 << ".\n";
        std::exit(2);
    }

    // now to decompress

    std::array<uint8_t, 4096> BUFFER; BUFFER.fill(0x00);
    uint8_t flags8;
    uint16_t writeidx = 0xFEE; // BUFFER write index
    uint16_t readidx;          // BUFFER read index
    unsigned int fidx = 0x10;  // index into arcdata

    while (fidx < arcdata.size()) {
        flags8 = arcdata.at(fidx);
        fidx++;
        for (int i=0; i<8; i++) {
            if (flags8 & 1) { // literal byte
                outdata.push_back(arcdata.at(fidx));
                BUFFER.at(writeidx) = arcdata.at(fidx);
                writeidx++; writeidx %= 4096;
                fidx++;
            } else { // run data, run!
                readidx = arcdata.at(fidx);
                fidx++;
                readidx |= (arcdata.at(fidx) & 0xF0) << 4;
                for (int j=0; j<(arcdata.at(fidx) & 0x0F)+3; j++) {
                    outdata.push_back(BUFFER.at(readidx));
                    BUFFER.at(writeidx) = BUFFER.at(readidx);
                    readidx++; readidx %= 4096;
                    writeidx++; writeidx %= 4096;
                }
                fidx++;
            }
            flags8 >>= 1;
            if (fidx >= arcdata.size()) break;
        }
    }

    if (decsize != outdata.size()) {
        std::cerr << "Size mismatch: got " << outdata.size() << " bytes after decompression, expected " << decsize << ".\n";
        std::exit(2);
    }

    return outdata;
}
