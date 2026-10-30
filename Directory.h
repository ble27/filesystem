/*
Directory is a file that contains data blocks with (filename, inode) pair.
A directory itself is a map that points a filename to an inode number.
*/

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <unordered_map>
#include "Inode.h"

struct Directory {
    std::string parent;
    std::unordered_map<std::string, uint64_t> dir;
    std::unordered_map<std::string, size_t> filename_len;
};

#endif