#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>


std::string readFileToString(const std::string& filename) {
    try {
        std::ifstream ifs(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
        size_t fileSize = (size_t)ifs.tellg();
        if(!fileSize) return std::string();
        ifs.seekg(0, std::ios::beg);
        std::vector<char> bytes(fileSize);
        ifs.read(&bytes[0], fileSize);
        return std::string(&bytes[0], fileSize);
    } catch (std::exception&) {}
    return std::string();
}


void die(std::string message) {
    std::cerr << message << std::endl;
    exit(-1);
}