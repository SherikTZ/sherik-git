#ifndef FILE_H
#define FILE_H

#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> readFileContents(std::string filepath);
int getFileSize(std::string filepath);
std::vector<char> readFileBinary(const std::string& filepath);

#endif