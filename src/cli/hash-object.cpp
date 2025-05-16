#include <string>
#include "hash-object.h"
#include "blob.h"
#include "init.h"

int hash_object(const std::string& filepath){


    std::string GIT_NOT_INITIALIZED = "sherikGit: git is not initialized.";

    if(!checkIfGitInitialized()){
        std::cerr << GIT_NOT_INITIALIZED << std::endl;
        return -1;
    }

    return writeBlobFile(filepath);

    }
