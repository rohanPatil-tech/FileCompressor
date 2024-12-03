#include "file_utils.h"
#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> splitFile(const std::string& filename, size_t chunkSize, const std::string& outputFolder) {
    std::ifstream inputFile(filename, std::ios::binary);
    std::vector<std::string> chunkPaths;

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return chunkPaths;
    }

    size_t chunkCount = 0;
    std::vector<char> buffer(chunkSize);

    while (inputFile) 
    {
        inputFile.read(buffer.data(), chunkSize);
        std::streamsize bytesRead = inputFile.gcount();

        if (bytesRead > 0) {
            std::string chunkPath = outputFolder + "/chunk" + std::to_string(chunkCount);
            std::ofstream outFile(chunkPath, std::ios::binary);
            outFile.write(buffer.data(), bytesRead);
            outFile.close();
            
            chunkPaths.push_back(chunkPath);
            chunkCount++;
        }
    }
    inputFile.close();
    return chunkPaths;
}