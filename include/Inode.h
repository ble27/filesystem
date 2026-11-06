/*
Inode is a data structure that contains the metadata of a file, including
permissions, file size, owners, and pointers to data blocks of the file contents.
*/

#ifndef INODE_H
#define INODE_H

#include <iostream>
#include <vector>
#include <atomic>

// std::atomic<uint64_t> CUR_INODE_NUM(0);
constexpr size_t BLOCK_SIZE = 4096;

enum class PERMISSIONS {
    RWX,
    RW,
    RX,
    WX,
    R,
    W,
    X,
    NONE
};

enum class FILE_TYPE {
    REGULAR, 
    DIRECTORY,
    SYMLINK
};

// Simplified version of the actual C implementation of an inode
// Each block is 4 KiB, each int pointer is 4 Bytes
// Each indirect block has 1024 ptrs
// Implement inode as a pointer

struct Inode {
    uint64_t ino;
    std::vector<PERMISSIONS> permissions; // USR | GRP | OTH
    FILE_TYPE file_type;
    uint64_t file_size = 0;
    std::vector<int*> dir_ptrs; // direct pointers
    uint64_t total_blocks = 0;   // index blocks + data blocks 
    uint64_t total_data_blocks = 0; // used by allocate_blocks() method 

    // Single indirect pointer
    // Each single indirect block stores 1024 pointers
    int* single_indir_ptr;

    // Double indirect pointer
    // Each double indrect block stores 1024^2 pointers (1024 single indirect blocks)
    int** double_indir_ptr; 
    
    // Triple indirect pointer
    // Each triple indirect block stores 1024^3 pointers
    int*** triple_indir_ptr;  

    // Hard link references
    uint8_t link_cnt; 

    Inode(): permissions(3), dir_ptrs(12) {
        // Default permissions -rw-------
        permissions[0] = PERMISSIONS::RW;
        permissions[1] = PERMISSIONS::NONE;
        permissions[2] = PERMISSIONS::NONE;

        for (size_t i = 0; i < 12; ++i) {
            dir_ptrs[i] = nullptr;
        }
    };
    // Clear the contents of all pointers and mark as nullptr
    // Reset hard link references, total block sizes, and file size
    void free_inode(Inode* inode);

    // IDX = 0 (USR)
    // IDX = 1 (GRP)
    // IDX = 2 (OTH)
    void modify_permissions(size_t idx, PERMISSIONS permissions);
    
    // Allocate the minimum number of blocks to store a file
    // Start from direct pointers to single to double to triple indirect blocks
    uint64_t allocate_blocks();

    // Align FILE_SIZE (# of BYTES) to be multiple of BLOCK_SIZE
    // For example, 1024 Bytes if 1 KiB, 4096 if 4 KiB
    void calculate_data_blocks(uint64_t FILE_SIZE);
};

#endif