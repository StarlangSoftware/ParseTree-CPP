//
// Created by Olcay Taner YILDIZ on 12.05.2022.
//

#include "catch.hpp"
#include "../ParallelTreeBank.h"

TEST_CASE("ParallelTreeBankTest-testTreeBank") {
    ParallelTreeBank parallelTreeBank = ParallelTreeBank("trees", "fileList.txt", "trees2", "fileList2.txt");
    REQUIRE(3 == parallelTreeBank.size());
}