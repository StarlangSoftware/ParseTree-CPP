//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../src/ParseTree.h"

TEST_CASE("ParseTreeTest-testNodeCount") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    REQUIRE(34 == parseTree1->nodeCount());
    REQUIRE(39 == parseTree2->nodeCount());
    REQUIRE(32 == parseTree3->nodeCount());
    REQUIRE(28 == parseTree4->nodeCount());
    REQUIRE(9 == parseTree5->nodeCount());
}

TEST_CASE("ParseTreeTest-testIsFullSentence") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    REQUIRE_FALSE(!parseTree1->isFullSentence());
    REQUIRE_FALSE(!parseTree2->isFullSentence());
    REQUIRE_FALSE(!parseTree3->isFullSentence());
    REQUIRE_FALSE(!parseTree4->isFullSentence());
    REQUIRE_FALSE(parseTree5->isFullSentence());
}

TEST_CASE("ParseTreeTest-testLeafCount") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    REQUIRE(13 == parseTree1->leafCount());
    REQUIRE(15 == parseTree2->leafCount());
    REQUIRE(10 == parseTree3->leafCount());
    REQUIRE(10 == parseTree4->leafCount());
    REQUIRE(4 == parseTree5->leafCount());
}

TEST_CASE("ParseTreeTest-testNodeCountWithMultipleChildren") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    REQUIRE(8 == parseTree1->nodeCountWithMultipleChildren());
    REQUIRE(9 == parseTree2->nodeCountWithMultipleChildren());
    REQUIRE(8 == parseTree3->nodeCountWithMultipleChildren());
    REQUIRE(6 == parseTree4->nodeCountWithMultipleChildren());
    REQUIRE(1 == parseTree5->nodeCountWithMultipleChildren());
}

TEST_CASE("ParseTreeTest-testWordCount") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    REQUIRE(7 == parseTree1->wordCount(true));
    REQUIRE(8 == parseTree2->wordCount(true));
    REQUIRE(6 == parseTree3->wordCount(true));
    REQUIRE(7 == parseTree4->wordCount(true));
    REQUIRE(2 == parseTree5->wordCount(true));
}

TEST_CASE("ParseTreeTest-testToSentence") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    REQUIRE("The complicated language in the huge new law has muddied the fight ." == parseTree1->toSentence());
    REQUIRE("The Ways and Means Committee will hold a hearing on the bill next Tuesday ." == parseTree2->toSentence());
    REQUIRE("We 're about to see if advertising works ." == parseTree3->toSentence());
    REQUIRE("This time around , they 're moving even faster ." == parseTree4->toSentence());
    REQUIRE("Ad Notes ... ." == parseTree5->toSentence());
}

TEST_CASE("ParseTreeTest-testConstituentSpan") {
    ParseTree *parseTree1, *parseTree2, *parseTree3, *parseTree4, *parseTree5;
    parseTree1 = new ParseTree("trees/0000.dev");
    parseTree2 = new ParseTree("trees/0001.dev");
    parseTree3 = new ParseTree("trees/0002.dev");
    parseTree4 = new ParseTree("trees/0003.dev");
    parseTree5 = new ParseTree("trees/0014.dev");
    ConstituentSpan span = parseTree1->constituentSpanList()[6];
    REQUIRE(Symbol("PP-LOC") == span.getConstituent());
    REQUIRE(4 == span.getStart());
    REQUIRE(9 == span.getEnd());
    span = parseTree2->constituentSpanList()[10];
    REQUIRE(Symbol("VB") == span.getConstituent());
    REQUIRE(7 == span.getStart());
    REQUIRE(8 == span.getEnd());
    span = parseTree3->constituentSpanList()[0];
    REQUIRE(Symbol("S") == span.getConstituent());
    REQUIRE(1 == span.getStart());
    REQUIRE(11 == span.getEnd());
    span = parseTree4->constituentSpanList()[5];
    REQUIRE(Symbol("ADVP") == span.getConstituent());
    REQUIRE(3 == span.getStart());
    REQUIRE(4 == span.getEnd());
    span = parseTree5->constituentSpanList()[4];
    REQUIRE(Symbol(".") == span.getConstituent());
    REQUIRE(4 == span.getStart());
    REQUIRE(5 == span.getEnd());
}