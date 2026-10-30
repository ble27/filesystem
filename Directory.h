/*
Directory is a file that contains data blocks with (filename, inode) pair.
A directory itself is a map that points a filename to an inode number.
*/

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Inode.h"
#include <iostream>
#include <unordered_map>
#include <atomic>
#include <cstdint>

extern std::atomic<uint64_t> CUR_INODE_NUM;

struct Directory {
    std::string parent = "";
    std::atomic<bool> isRoot{false};
    std::unordered_map<std::string, uint64_t> dir;
    std::unordered_map<std::string, size_t> filename_len;

    // Find a free inode, initialize the inode, and create a directory entry
    void add_directory_entry(std::string filename); 

    // Unlink a filename from an inode, but doesn't free the inode until the hard link count is 0
    void remove_directory_entry(std::string filename); 

    std::string parent_directory(); 

    // Find the corresponding inode number value of a filename key
    // Returns inode number if filename pair exists
    // Returns -1 if not filename not found
    int lookup_filename(std::string filename); 
};

#endif