#include "file_utils.h"
#include <iostream>
#include <fstream>
#include <vector>

// void splitFile(const std::string& filename, size_t chunkSize) {
//     std::ifstream inputFile(filename, std::ios::binary);
//     std::cout << "Attempting to open file: " << filename << std::endl;

//     if (!inputFile) {
//         std::cerr << "Error opening file: " << filename << std::endl;
//         return;
//     }

//     size_t chunkCount = 0;
//     std::vector<char> buffer(chunkSize);

//     while (inputFile) {
//         inputFile.read(buffer.data(), chunkSize);
//         std::streamsize bytesRead = inputFile.gcount();

//         if (bytesRead > 0) {
//             std::ofstream outFile(filename + "_chunk" + std::to_string(chunkCount), std::ios::binary);
//             outFile.write(buffer.data(), bytesRead);
//             outFile.close();
//             chunkCount++;
//         }
//     }

//     inputFile.close();
//     std::cout << "File split into " << chunkCount << " chunks." << std::endl;
// }

void splitFile(const std::string& filename, size_t chunkSize, const std::string& outputFolder) {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    char* buffer = new char[chunkSize];
    size_t partNumber = 0;

    while (inputFile) {
        inputFile.read(buffer, chunkSize);
        std::streamsize bytesRead = inputFile.gcount();

        if (bytesRead > 0) {
            std::string chunkFileName = outputFolder + "/chunk_" + std::to_string(partNumber++) + ".bin";
            std::ofstream outputFile(chunkFileName, std::ios::binary);
            outputFile.write(buffer, bytesRead);
            outputFile.close();
        }
    }

    delete[] buffer;
    inputFile.close();
}
