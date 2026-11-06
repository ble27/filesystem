#include <catch2/catch_test_macros.hpp>
#include "Inode.h"

TEST_CASE("Inode blocks allocation", "[allocate_blocks]" ) {
    Inode inode;
    
    // Direct pointers
    SECTION("Direct pointers test") {
        inode.total_data_blocks = 11;
        REQUIRE(inode.allocate_blocks() == 0);
    }
    // Single indirect pointer
    SECTION("Single indirect pointer test") {
        inode.total_data_blocks = 1036;
        REQUIRE(inode.allocate_blocks() == 1);
    }
    // Double indirect pointer
    SECTION("Double indirect pointer test") {
        inode.total_data_blocks = 1049612;
        REQUIRE(inode.allocate_blocks() == 2);
    }
    // Triple indirect pointer 
    SECTION("Triple indirect pointer test") {
        inode.total_data_blocks = 1049613;
        REQUIRE(inode.allocate_blocks() == 3);
        inode.total_data_blocks = 1074791436;
        REQUIRE(inode.allocate_blocks() == 3); 
    }
    SECTION("Beyond triple indirect pointer test") {
        inode.total_data_blocks = 1074791437;
        REQUIRE_THROWS(inode.allocate_blocks());
    }
};