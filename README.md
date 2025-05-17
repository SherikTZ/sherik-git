Currently supported commands:

sherikGit init: initializes an empty git directory in the current directory with all necessary directories and files to support git.
sherikGit hash-object <filepath> - writes a file as BLOB (Binary Large Object) regardless of file type and stores it using SHA256.
sherikGit cat-file: allows inspection of files written by sherikGit. Types include:
-p: pretty prints the object based on its type.
-t: prints object type
-s: prints objects original size (not including header, whitespace between header and size, size and a a null byte)
