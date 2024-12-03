#ifndef MULTITHREADING_UTILS_H
#define MULTITHREADING_UTILS_H

#include <thread>
#include <vector>

void startCompressionThreads(const std::string& filename, size_t chunkSize);

#endif
