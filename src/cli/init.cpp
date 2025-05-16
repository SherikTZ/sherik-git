#include <filesystem>
#include <iostream>
#include <string>
#include "init.h"

int init(){

    if(!checkIfGitInitialized()){

    std::filesystem::create_directory(".git");
    std::filesystem::create_directory(".git/objects");
    std::filesystem::create_directory(".git/objects/info");
    std::filesystem::create_directory(".git/objects/packs");
    std::filesystem::create_directory(".git/refs");
    std::filesystem::create_directory(".git/refs/heads");
    std::filesystem::create_directory(".git/refs/tags");

    }

    return 0;
}

bool checkIfGitInitialized(){

    std::string GIT_ALREADY_EXITS = "Git already exists.";

    std::filesystem::path dir = ".git";

    if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)){
        return 1;
    }
    else {
        return 0;
    }

}