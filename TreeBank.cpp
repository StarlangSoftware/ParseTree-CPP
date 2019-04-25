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
            ParseTree tree = ParseTree(treeLine);
            if (tree.getRoot() != nullptr){
                parseTrees.push_back(tree);
            }
            treeLine = "";
        }
        getline(inputFile, line);
    }
}

void TreeBank::stripPunctuation() {
    for (ParseTree tree : parseTrees){
        tree.stripPunctuation();
    }
}

int TreeBank::size() {
    return parseTrees.size();
}

int TreeBank::wordCount(bool excludeStopWords) {
    int count = 0;
    for (ParseTree tree:parseTrees){
        count += tree.wordCount(excludeStopWords);
    }
    return count;
}

void TreeBank::save(string fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ostream::out);
    for (ParseTree parseTree : parseTrees){
        outputFile << "( ";
        outputFile << parseTree.to_string();
        outputFile << " )\n";
    }
    outputFile.close();
}

ParseTree TreeBank::get(int index) {
    return parseTrees.at(index);
}

int TreeBank::countWords(bool excludeStopWords) {
    int count = 0;
    for (ParseTree tree : parseTrees){
        count += tree.wordCount(excludeStopWords);
    }
    return count;
}

TreeBank::TreeBank(string folder, string fileList) {
    ifstream treeBankFile, parseTreeFile;
    string line;
    treeBankFile.open(fileList, ifstream::in);
    while (treeBankFile.good()){
        treeBankFile >> line;
        string fileName = folder;
        fileName += "/" + line;
        parseTreeFile.open(fileName, ifstream::in);
        ParseTree parseTree = ParseTree(parseTreeFile);
        parseTrees.push_back(parseTree);
        parseTreeFile.close();
    }
    treeBankFile.close();
}
