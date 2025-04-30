#include "Utils.hpp"
#include "Error.hpp"
#include <chrono>
#include <regex>
#include <sstream>
#include <string>
#include <thread>

#ifdef _WIN32
void setConsoleSize(int width, int height) {
    std::string command = "mode con: cols=" + std::to_string(width) + " lines=" + std::to_string(height);
    system(command.c_str());
}

#else
void setConsoleSize(int width, int height) {
    std::string command = "stty cols " + std::to_string(width) + " rows " + std::to_string(height);
    system(command.c_str());
}
#endif

void delayTime(long long ms) {
    throw NotImplement("`delayTime` not implement");
}

std::string stripAnsi(const std::string& text) {
    throw NotImplement("`stripAnsi` not implement");
}

std::pair<int, int> getBoardPosition(int posIndex, int mapSize) {
    throw NotImplement("`getBoardPosition` not implement");
}

void delayMilliseconds(int ms) {
    throw NotImplement("`delayMilliseconds` not implement");
}

std::vector<std::string> split(const std::string& str) {
    throw NotImplement("`split` not implement");
}
