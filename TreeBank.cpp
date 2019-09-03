//
// Created by Olcay Taner YILDIZ on 2019-04-23.
//

#include <fstream>
#include "TreeBank.h"

TreeBank::TreeBank(istream& inputFile) {
    string line, treeLine;
    int parenthesisCount = 0;
    getline(inputFile, line);
    treeLine = "";
    while (!line.empty()){
        for (char ch : line) {
            if (ch == '('){
                parenthesisCount++;
            } else {
                if (ch == ')'){
                    parenthesisCount--;
                }
            }
        }
        treeLine += line;
        if (parenthesisCount == 0){
            auto* tree = new ParseTree(treeLine);
            if (tree->getRoot() != nullptr){
                parseTrees.push_back(tree);
            }
            treeLine = "";
        }
        getline(inputFile, line);
    }
}

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
 * Obsolete function of the {@link TreeBank} class. If the contents of all the parseTree's must be inside a
 * single file, this function saves all the ParseTree's in a single file. Each line in this file corresponds to a
 * single ParseTree.
 * @param fileName Output file that will contain the parse trees.
 */
void TreeBank::save(const string& fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ostream::out);
    for (ParseTree* parseTree : parseTrees){
        outputFile << "( ";
        outputFile << parseTree->to_string();
        outputFile << " )\n";
    }
    outputFile.close();
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
