#include <Directory.h>

std::string Directory::parent_directory() {
    return (isRoot ? "/" : parent);
}

void Directory::add_directory_entry(std::string filename) { 
    if (dir.find(filename) == dir.end()) {
        CUR_INODE_NUM++;
        dir[filename] = CUR_INODE_NUM;
    }
}

void Directory::remove_directory_entry(std::string filename) {
    if (dir.find(filename) == dir.end()) return;
    dir.erase(filename);
}

int Directory::lookup_filename(std::string filename) {
    return dir.count(filename) ? dir[filename] : -1;
}