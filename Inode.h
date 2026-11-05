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
// Each block is 4 KiB, each int pointer is 4 Bytes
// Each indirect block has 1024 ptrs
// Implement inode as a pointer

struct Inode {
    uint64_t ino;
    std::vector<PERMISSIONS> permissions; // USR | GRP | OTH
    FILE_TYPE file_type;
    uint64_t file_size = 0;
    std::vector<int*> dir_ptrs; // direct pointers
    int total_block_size = 0;    

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

    Inode(): permissions(3), dir_ptrs(12) {};
    
    void free_inode(Inode* inode);
    void modify_permissions();
    
    // Allocate the minimum number of blocks to store a file
    // Start from direct pointers to single to double to triple indirect blocks
    void allocate_blocks();

    // Count the total data blocks (file content) + index blocks (blocks that leads to data blocks)
    uint64_t total_blocks();

    // ceil(File size / 4 KiB)
    // Implement using alignas to align as multiples of base 2
    // FILE_SIZE = # of BYTES
    // For example, 1024 Bytes if 1 KiB, 4096 if 4 KiB
    uint64_t data_blocks_needed(uint64_t FILE_SIZE);
};

#endif