//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "../Symbol.h"

TEST_CASE("SymbolTest-trimSymbol") {
    REQUIRE("NP" == Symbol("NP-SBJ").trimSymbol().getName());
    REQUIRE("VP" == Symbol("VP-SBJ-2").trimSymbol().getName());
    REQUIRE("NNP" == Symbol("NNP-SBJ-OBJ-TN").trimSymbol().getName());
    REQUIRE("S" == Symbol("S-SBJ=OBJ").trimSymbol().getName());
}