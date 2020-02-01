//
// Created by Olcay Taner YILDIZ on 2019-04-23.
//

#include <fstream>
#include "TreeBank.h"

/**
 * Strips punctuation symbols from all parseTrees in this TreeBank.
 */
void TreeBank::stripPunctuation() {
    for (ParseTree* tree : parseTrees){
        tree->stripPunctuation();
    }
}

/**
 * Returns number of trees in the TreeBank.
 * @return Number of trees in the TreeBank.
 */
int TreeBank::size() {
    return parseTrees.size();
}

/**
 * Returns number of words in the parseTrees in the TreeBank. If excludeStopWords is true, stop words are not
 * counted.
 * @param excludeStopWords If true, stop words are not included in the count process.
 * @return Number of all words in all parseTrees in the TreeBank.
 */
int TreeBank::wordCount(bool excludeStopWords) {
    int count = 0;
    for (ParseTree* tree:parseTrees){
        count += tree->wordCount(excludeStopWords);
    }
    return count;
}

/**
 * Accessor for a single ParseTree.
 * @param index Index of the parseTree.
 * @return The ParseTree at the given index.
 */
ParseTree* TreeBank::get(int index) {
    return parseTrees.at(index);
}

/**
 * A constructor of {@link TreeBank} class which reads all {@link ParseTree] files inside the given folder. For each
 * file inside that folder, the constructor creates a ParseTree and puts in inside the list parseTrees.
 */
TreeBank::TreeBank(const string& folder, const string& fileList) {
    ifstream treeBankFile, parseTreeFile;
    string line;
    treeBankFile.open(fileList, ifstream::in);
    while (treeBankFile.good()){
        treeBankFile >> line;
        string fileName = folder;
        fileName += "/" + line;
        parseTreeFile.open(fileName, ifstream::in);
        auto* parseTree = new ParseTree(parseTreeFile);
        parseTrees.push_back(parseTree);
        parseTreeFile.close();
    }
    treeBankFile.close();
}

TreeBank::~TreeBank() {
    for (ParseTree* tree : parseTrees){
        delete tree;
    }
}
