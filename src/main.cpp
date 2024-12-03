#include "file_utils.h"
#include "constants.h" 
#include <unistd.h>  // For getcwd
#include <limits.h>  // For PATH_MAX
#include <filesystem>   
#include <iostream>
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

    for (const auto& entry : std::filesystem::directory_iterator(input)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();        
            std::string fileName = entry.path().stem().string(); 
            std::string outputFolder = input + fileName;
            std::filesystem::create_directory(outputFolder);
            splitFile(filePath, CHUNK_SIZE, outputFolder);      
        }
    }

    return 0;
}
