#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

void splitFile(const std::string& filename, size_t chunkSize);
void splitFile(const std::string& filename, size_t chunkSize, const std::string& outputFolder);

void mergeChunks(const std::string& outputFile);

#endif // FILE_UTILS_H
