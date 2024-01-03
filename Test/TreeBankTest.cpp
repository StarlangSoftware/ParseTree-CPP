//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../src/TreeBank.h"

TEST_CASE("TreeBankTest-testTreeBank") {
    TreeBank treeBank1 = TreeBank("trees");
    REQUIRE(5 == treeBank1.size());
    REQUIRE(30 == treeBank1.wordCount(true));
}