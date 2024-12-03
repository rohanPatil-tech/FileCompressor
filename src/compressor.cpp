#include "compressor.h"
#include <zlib.h>

std::vector<char> compressData(const std::vector<char>& data) {
    uLongf compressedSize = compressBound(data.size()); 
    std::vector<char> compressedData(compressedSize);

    int result = compress(reinterpret_cast<Bytef*>(compressedData.data()), &compressedSize,
                          reinterpret_cast<const Bytef*>(data.data()), data.size());

    if (result != Z_OK) {
        throw std::runtime_error("Compression failed!");
    }

    compressedData.resize(compressedSize);
    return compressedData;
}
