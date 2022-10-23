//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//
#include "catch.hpp"
#include "../src/ParseTree.h"
#include "../src/LeafAncestorMetric.h"
#include "../src/ModifiedLeafAncestorMetric.h"
#include "../src/ParsevalMetric.h"
#include "../src/ModifiedParsevalMetric.h"

TEST_CASE("testLeafAncestor") {
    auto* metric = new LeafAncestorMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("../turkish1", "../turkish2"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.8560941043083901 == vector[0] / vector[1]);
}

TEST_CASE("testParsevalMetric") {
    auto* metric = new ParsevalMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("../turkish1", "../turkish2"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.5060545935545936 == vector[2]);
}

TEST_CASE("testModifiedParsevalMetric") {
    auto* metric = new ModifiedParsevalMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("../turkish1", "../turkish2"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.484297091103383 == vector[2]);
}