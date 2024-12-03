#include "file_utils.h"
#include "constants.h" 
#include "compressor.h"
#include <unistd.h>  
#include <limits.h>
#include <filesystem>   
#include <iostream>
#include <fstream>
int main() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << std::endl;
    }

    const std::string input = INPUT_LOC;
    if (!std::filesystem::exists(input)) {
        std::cerr << "Input folder does not exist!" << std::endl;
        return 1;
    }

    for (const auto& entry : std::filesystem::directory_iterator(input)) 
    {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();        
            std::string fileName = entry.path().stem().string(); 
            std::string outputFolder = input + fileName + "_chunks/";
            std::filesystem::create_directory(outputFolder);

            std::vector<std::string> chunkPaths = splitFile(filePath, CHUNK_SIZE, outputFolder);

            for (const auto& chunkPath : chunkPaths) 
            {
                std::ifstream chunkFile(chunkPath, std::ios::binary);
                std::vector<char> buffer((std::istreambuf_iterator<char>(chunkFile)), std::istreambuf_iterator<char>());
                chunkFile.close();

                std::vector<char> compressedData = compressData(buffer);

                std::string compressedFilePath = chunkPath + ".compressed";
                std::ofstream compressedFile(compressedFilePath, std::ios::binary);
                compressedFile.write(compressedData.data(), compressedData.size());
                compressedFile.close();
            }

            std::cout << "Compressed all chunks for file: " << fileName << std::endl;
        }
    }
    return 0;
}
