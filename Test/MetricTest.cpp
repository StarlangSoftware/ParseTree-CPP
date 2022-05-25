//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//
#include "catch.hpp"
#include "../ParseTree.h"
#include "../LeafAncestorMetric.h"
#include "../ModifiedLeafAncestorMetric.h"
#include "../ParsevalMetric.h"
#include "../ModifiedParsevalMetric.h"

TEST_CASE("testLeafAncestor") {
    LeafAncestorMetric* metric = new LeafAncestorMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("turkish1", "turkishFileList.txt", "turkish2", "turkishFileList.txt"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.8560941043083901 == vector[0] / vector[1]);
}

TEST_CASE("testModifiedLeafAncestor") {
    ModifiedLeafAncestorMetric* metric = new ModifiedLeafAncestorMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("turkish1", "turkishFileList.txt", "turkish2", "turkishFileList.txt"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.8741496598639455 == vector[0] / vector[1]);
}

TEST_CASE("testParsevalMetric") {
    ParsevalMetric* metric = new ParsevalMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("turkish1", "turkishFileList.txt", "turkish2", "turkishFileList.txt"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.5060545935545936 == vector[2]);
}

TEST_CASE("testModifiedParsevalMetric") {
    ModifiedParsevalMetric* metric = new ModifiedParsevalMetric();
    vector<vector<double>> matrix = metric->calculate(new ParallelTreeBank("turkish1", "turkishFileList.txt", "turkish2", "turkishFileList.txt"));
    vector<double> vector = metric->average(matrix);
    REQUIRE(0.484297091103383 == vector[2]);
}