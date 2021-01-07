//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../ParseTree.h"
#include "../NodeCollector.h"
#include "../NodeCondition/IsLeaf.h"
#include "../NodeCondition/IsEnglishLeaf.h"

TEST_CASE("NodeCollectorTest-testCollectLeaf") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    NodeCollector nodeCollector1 = NodeCollector(parseTree1->getRoot(), new IsLeaf());
    REQUIRE(13 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree2->getRoot(), new IsLeaf());
    REQUIRE(15 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree3->getRoot(), new IsLeaf());
    REQUIRE(10 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree4->getRoot(), new IsLeaf());
    REQUIRE(10 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree5->getRoot(), new IsLeaf());
    REQUIRE(4 == nodeCollector1.collect().size());
}

TEST_CASE("NodeCollectorTest-testCollectEnglish") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    NodeCollector nodeCollector1 = NodeCollector(parseTree1->getRoot(), new IsEnglishLeaf());
    REQUIRE(13 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree2->getRoot(), new IsEnglishLeaf());
    REQUIRE(15 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree3->getRoot(), new IsEnglishLeaf());
    REQUIRE(9 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree4->getRoot(), new IsEnglishLeaf());
    REQUIRE(10 == nodeCollector1.collect().size());
    nodeCollector1 = NodeCollector(parseTree5->getRoot(), new IsEnglishLeaf());
    REQUIRE(4 == nodeCollector1.collect().size());
}