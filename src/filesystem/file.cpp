#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> readFileContents(const std::string& filepath){
    std::vector<std::string> fileContents = {};
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error: File could not be opened." << std::endl;
        return fileContents;
    }

    std::string line;

    while (std::getline(file, line)) {
        fileContents.push_back(line);
    }

    file.close();

    return fileContents;

}

int getFileSize(const std::string& filepath){
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return -1;
    }
    return file.tellg();
}

std::vector<char> readFileBinary(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);

    if (!file) {
        std::cerr << "Error: Could not open file for binary reading." << std::endl;
        return {};
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Error: Could not read entire file." << std::endl;
        return {};
    }

    return buffer;
}