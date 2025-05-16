#include <string>
#include <iostream>
#include "init.h"
#include "hash-object.h"

int cli(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "sherikGit: No command provided." << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        init();
    }
    else if (command == "hash-object")
    {
        std::string filepath = argv[2];
        hash_object(filepath);
    }
    

    return 0;
}