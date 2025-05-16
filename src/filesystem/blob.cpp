#include "file.h"
#include "SHA256.h"
#include "init.h"
#include <filesystem>
#include <vector>

int writeBlobFile(const std::string& filepath) {

    std::vector<char> originalContent = readFileBinary(filepath);

    if (originalContent.empty()) {
        std::cerr << "Error reading file or file is empty.\n";
        return -1;
    }

    std::string FILE_TYPE = "blob";
    int size = static_cast<int>(originalContent.size());
    std::string header = FILE_TYPE + " " + std::to_string(size) + '\0';

    std::vector<uint8_t> combinedData;
    combinedData.reserve(header.size() + originalContent.size());
    combinedData.insert(combinedData.end(), header.begin(), header.end());
    combinedData.insert(combinedData.end(), originalContent.begin(), originalContent.end());

    SHA256 sha;
    sha.update(combinedData.data(), combinedData.size());
    std::string hashString = sha.toString(sha.digest());

    std::string blobDir = hashString.substr(0, 2);
    std::string hashStringTrimmed = hashString.substr(2, hashString.length() - 1);

    std::string blobDirPath = ".git/objects/" + blobDir;

    std::filesystem::create_directory(blobDirPath);

    std::string outFilepath = blobDirPath + "/" + hashStringTrimmed;

    std::ofstream outFile(outFilepath, std::ios::binary);

    if (!outFile) {
        std::cerr << "Error creating output file.\n";
        return -1;
    }

    outFile.write(reinterpret_cast<const char*>(combinedData.data()), combinedData.size());

    if (!outFile.good()) {
         std::cerr << "Error: Failed to write all data to object file: " << hashString << std::endl;
         outFile.close();
         return -1;
    }
    outFile.close();

    return 0;
}
