#include "../include/Inode.h"

void Inode::free_inode(Inode* inode) {
    inode->file_size = 0;
    inode->link_cnt = 0;
    inode->file_size = 0;
    
    for (size_t i = 0; i < inode->dir_ptrs.size(); ++i) {
        delete dir_ptrs[i];
        dir_ptrs[i] = nullptr;
    }
}

void Inode::modify_permissions(size_t idx, PERMISSIONS perm) {
    if (idx > 2) {
        std::cout << "Invalid index: Please choose from 0 (USR), 1 (GRP), or 2 (OTH) to modify permissions.\n";
    }
    if (permissions[idx] == perm) return;
    permissions[idx] = perm; 
}

void Inode::calculate_data_blocks(uint64_t file_size) {
    // Aligned FILE_SIZE to be the next multiple of BLOCK_SIZE
    // Adding BLOCK_SIZE - 1 moves to the next bucket
    total_data_blocks = ((file_size + BLOCK_SIZE - 1)  / BLOCK_SIZE);
}

uint64_t Inode::allocate_blocks() {
    // Precomputation to check which index block level is needed
    bool single_idx = false, double_idx = false, triple_idx = false;
    // All the file blocks are reachable via 12 direct pointers
    if (total_data_blocks <= 12) {
        return 0;
    }

    // File blocks require 12 direct pointers + 1 single index block
    uint64_t single_rng = total_data_blocks - 12;
    if (single_rng <= 1024) {
        single_idx = true;
        std::cout << "Single index block needed.\n";
        return 1;
    }

    uint64_t double_rng = single_rng - 1024;
    if (double_rng <= 1024 * 1024) {
        single_idx = true;
        double_idx = true;
        std::cout << "Double index block needed.\n";
        return 2;
    }

    uint64_t triple_rng = double_rng - 1024 * 1024;
    if (triple_rng <= 1024 * 1024 * 1024) {
        single_idx = true;
        double_idx = true;
        triple_idx = true;
        std::cout << "Triple index block needed.\n";
        return 3;
    }

    // Beyond 1024^3 exceeds the limit of the filesystem
    if (triple_rng - 1024 * 1024 * 1024 > 0) {
        throw std::runtime_error("File size exceeds the limit of the filesystem.\n");
    }
}  