//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include <ostream>
#include <fstream>
#include "ParseTree.h"
#include "NodeCollector.h"
#include "NodeCondition/IsEnglishLeaf.h"

const vector<string> ParseTree::sentenceLabels = {"SINV", "SBARQ", "SBAR", "SQ", "S"};

ParseTree::ParseTree(ParseNode *root) {
    this->root = root;
}

ParseTree::ParseTree(string line) {
    line = Word::replaceAll(line, "\n", "");
    line = Word::replaceAll(line, "\t", "");
    if (line.find('(') != string::npos && line.find_last_of(')') != string::npos){
        line = Word::trim(line.substr(line.find('(') + 1, line.find_last_of(')') - line.find('(') - 1));
        root = new ParseNode(nullptr, line, false);
    } else {
        root = nullptr;
    }
}

ParseTree::ParseTree(istream &inputFile) {
    string line;
    getline(inputFile, line);
    if (line.find('(') != string::npos && line.find_last_of(')') != string::npos){
        line = Word::trim(line.substr(line.find('(') + 1, line.find_last_of(')') - line.find('(') - 1));
        root = new ParseNode(nullptr, line, false);
    } else {
        root = nullptr;
    }
}

ParseNode *ParseTree::nextLeafNode(ParseNode *parseNode) {
    NodeCollector nodeCollector = NodeCollector(root, new IsEnglishLeaf());
    vector<ParseNode*> leafList = nodeCollector.collect();
    for (int i = 0; i < leafList.size() - 1; i++){
        if (leafList.at(i) == parseNode){
            return leafList.at(i + 1);
        }
    }
    return nullptr;
}

ParseNode *ParseTree::previousLeafNode(ParseNode *parseNode) {
    NodeCollector nodeCollector = NodeCollector(root, new IsEnglishLeaf());
    vector<ParseNode*> leafList = nodeCollector.collect();
    for (int i = 1; i < leafList.size(); i++){
        if (leafList.at(i) == parseNode){
            return leafList.at(i - 1);
        }
    }
    return nullptr;
}

int ParseTree::nodeCountWithMultipleChildren() {
    return root->nodeCountWithMultipleChildren();
}

int ParseTree::nodeCount() {
    return root->nodeCount();
}

int ParseTree::leafCount() {
    return root->leafCount();
}

bool ParseTree::isFullSentence() {
    if (root != nullptr && Symbol::contains(sentenceLabels, root->getData().getName())){
        return true;
    }
    return false;
}

void ParseTree::save(const string& fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ostream::out);
    outputFile << "( ";
    outputFile << to_string();
    outputFile << " )\n";
    outputFile.close();
}

string ParseTree::to_string() {
    return root->to_string();
}

void ParseTree::correctParents() {
    root->correctParents();
}

void ParseTree::removeXNodes() {
    root->removeXNodes();
}

void ParseTree::stripPunctuation() {
    root->stripPunctuation();
}

ParseNode *ParseTree::getRoot() {
    return root;
}

string ParseTree::toSentence() {
    return root->toSentence();
}

int ParseTree::wordCount(bool excludeStopWords) {
    return root->wordCount(excludeStopWords);
}

ParseTree::~ParseTree() {
    delete root;
}
