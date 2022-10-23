//
// Created by Olcay Taner YILDIZ on 12.05.2022.
//

#include "catch.hpp"
#include "../src/ParallelTreeBank.h"

TEST_CASE("ParallelTreeBankTest-testTreeBank") {
    ParallelTreeBank parallelTreeBank = ParallelTreeBank("../trees", "../trees2");
    REQUIRE(3 == parallelTreeBank.size());
}