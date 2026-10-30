/*
Inode is a data structure that contains the metadata of a file, including
permissions, file size, owners, and pointers to data blocks of the file contents.
*/

#ifndef INODE_H
#define INODE_H

#include <iostream>
#include <vector>
#include <atomic>

std::atomic<uint64_t> CUR_INODE_NUM(0);

enum class PERMISSIONS {
    RWX,
    RW,
    RX,
    WX,
    R,
    W,
    X,
};

enum class FILE_TYPE {
    REGULAR, 
    DIRECTORY,
    SYMLINK
};

// Simplified version of the actual C implementation of an inode
struct Inode {
    uint64_t ino;
    std::vector<PERMISSIONS> permissions; // USR | GRP | OTH
    FILE_TYPE file_type;
    uint64_t file_size = 0;
    std::vector<int*> dir_ptrs; // direct pointers
    int* single_indir_ptr; // single indirect pointer
    int* double_indir_ptr; // double indirect pointer
    int* triple_indir_ptr;  // triple indirect pointer
    int link_cnt; // hard link references

    Inode(): permissions(3), dir_ptrs(12) {};

    void free_inode();
    void modify_permissions();
};

#endif