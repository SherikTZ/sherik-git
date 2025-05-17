#ifndef CAT_FILE_H
#define CAT_FILE_H

int cat_file(std::string type, std::string blobSHA256);
int cat_file_p(std::string fullPath);
int cat_file_t(std::string fullPath);
int cat_file_s(std::string fullPath);
int objectExists(std::string filepath);
std::string extractHeader(std::vector<char> buffer);
int extractSize(std::vector<char> buffer);
int cat_file_p_blob(std::vector<char> buffer);
#endif