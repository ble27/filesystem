#include "Inode.h"

void Inode::free_inode(Inode* inode) {
    inode->file_size = 0;
    inode->link_cnt = 0;
    inode->file_size = 0;
    
    for (size_t i = 0; i < inode->dir_ptrs.size(); ++i) {
        // Delete the file content first
        delete dir_ptrs[i];
        // Mark pointers as null
        dir_ptrs[i] = nullptr;
    }
}

void Inode::modify_permissions() {}

