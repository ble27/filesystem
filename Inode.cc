#include "Inode.h"

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

uint64_t Inode::data_blocks_needed(uint64_t file_size) {
    // Aligned FILE_SIZE to be the next multiple of BLOCK_SIZE
    // Adding BLOCK_SIZE - 1 moves to the next bucket
    uint64_t total_aligned_blocks = ((file_size + BLOCK_SIZE - 1)  / BLOCK_SIZE);
    return total_aligned_blocks;
}