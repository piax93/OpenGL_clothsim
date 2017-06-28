#pragma once

#include <string>

/**
 * Print error message and exit
 */
void die(std::string message);

/**
 * Read entire text file to string
 * @param filename Path to file
 */
std::string readFileToString(const std::string& filename);