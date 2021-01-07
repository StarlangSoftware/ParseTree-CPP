//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../TreeBank.h"

TEST_CASE("TreeBankTest-testTreeBank") {
    TreeBank treeBank1 = TreeBank("trees", "fileList.txt");
    REQUIRE(5 == treeBank1.size());
    REQUIRE(36 == treeBank1.wordCount(true));
}