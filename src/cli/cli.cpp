#include <string>
#include <iostream>
#include "init.h"
#include "hash-object.h"
#include "cat-file.h"

int cli(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cout << "sherikGit: No command provided." << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "init")
    {
        init();
    }
    else if (command == "hash-object")
    {
        if (argc < 3)
        {
            std::cout << "sherikGit: hash-object requires 1 argument but 0 were given" << std::endl;
            return 1;
        }
        std::string filepath = argv[2];
        hash_object(filepath);
    }

    if (command == "cat-file")
    {

        if (argc < 4)
        {
            std::cout << "sherikGit: cat-file requires 2 arguments but " << (argc - 2) << " were given" << std::endl;
        }

        std::string type = argv[2];
        std::string blobSHA256 = argv[3];
        return cat_file(type, blobSHA256);
    }

    return 0;
}