#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include "cat-file.h"
#include "file.h"

int cat_file(std::string type, std::string blobSHA256)
{

    std::string defaultPath = ".git/objects/";
    std::string prefix = blobSHA256.substr(0, 2);
    std::string suffix = blobSHA256.substr(2, blobSHA256.length() - 1);

    std::string fullPath = defaultPath + prefix + "/" + suffix;

    if (!objectExists(fullPath))
    {
        std::cerr << "sherikGit: error, no object with specified name is found" << std::endl;
        return -1;
    }

    if (type == "-p")
    {
        return cat_file_p(fullPath);
    }
    else if (type == "-t")
    {
        return cat_file_t(fullPath);
    }
    else if (type == "-s")
    {
        return cat_file_s(fullPath);
    }
    else
    {
        std::cerr << "sherikGit: unknown type " + type + "." << std::endl;
    }
}

int cat_file_p(std::string fullPath)
{

    std::vector<char> buffer = readFileBinary(fullPath);
    std::string header = extractHeader(buffer);
    if (header == "null")
    {
        std::cerr << "sherikGit: error, the provided object does not contain a valid header" << std::endl;
    }
    else if (header == "blob")
    {
        return cat_file_p_blob(buffer);
    }
}

int cat_file_t(std::string fullPath)
{
    std::vector<char> buffer = readFileBinary(fullPath);
    std::string header = extractHeader(buffer);
    if (header == "null")
    {
        std::cerr << "sherikGit: error, the provided object does not contain a valid header" << std::endl;
        return -1;
    }
    std::cout << header << std::endl;
    return 0;
}

int cat_file_s(std::string fullPath)
{
    std::vector<char> buffer = readFileBinary(fullPath);
    int size = extractSize(buffer);
    if (size == -1)
    {
        std::cerr << "sherikGit: error, file does not contain valid metadata about size" << std::endl;
        return -1;
    }
    std::cout << size << std::endl;
    return 0;
}

int objectExists(std::string filepath)
{
    return std::filesystem::exists(filepath);
}

std::string extractHeader(std::vector<char> buffer)
{
    /*
    Valid Headers:
    blob
    tree
    commit
    tag
    */

    int INITIAL_POS = 0;
    int MAX_POS = 5; // "commit" is longest valid header and can span [0, 5], hence MAX_POS is 5.

    std::string header = "";

    for (int pos = INITIAL_POS; pos <= MAX_POS; pos++)
    {
        header.push_back(buffer[pos]);
        if (header == "blob" || header == "tree" || header == "commit" || header == "tag")
        {
            return header;
        }
    }
    return "null";
}

int extractSize(std::vector<char> buffer)
{

    std::string header = extractHeader(buffer);
    int START_POS;
    if (header == "blob" || header == "tree")
    {
        START_POS = 5;
    }
    else if (header == "commit")
    {
        START_POS = 7;
    }
    else if (header == "tag")
    {
        START_POS = 4;
    }
    else
    {
        return -1;
    }

    std::string size = "";

    while (buffer[START_POS] != '\0')
    {
        char digit = buffer[START_POS];
        if (!std::isdigit(digit))
        {
            return -1;
        }

        size += buffer[START_POS];
        START_POS += 1;
    }

    return std::stoi(size);
}

int cat_file_p_blob(std::vector<char> buffer)
{
    int INITIAL_POS = 0;
    while (buffer[INITIAL_POS] != '\0')
    {
        INITIAL_POS++;
    }
    int startIndex = INITIAL_POS + 1;
    for (size_t i = startIndex; i < buffer.size(); i++)
    {
        std::cout << buffer[i];
    }
    return 0;
}