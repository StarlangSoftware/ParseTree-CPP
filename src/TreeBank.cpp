//
// Created by Olcay Taner YILDIZ on 2019-04-23.
//

#include <fstream>
#include "TreeBank.h"
using std::filesystem::directory_iterator;

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
int TreeBank::size() const{
    return parseTrees.size();
}

/**
 * Returns number of words in the parseTrees in the TreeBank. If excludeStopWords is true, stop words are not
 * counted.
 * @param excludeStopWords If true, stop words are not included in the count process.
 * @return Number of all words in all parseTrees in the TreeBank.
 */
int TreeBank::wordCount(bool excludeStopWords) const{
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
ParseTree* TreeBank::get(int index) const{
    return parseTrees.at(index);
}

/**
 * A constructor of {@link TreeBank} class which reads all {@link ParseTree] files inside the given folder. For each
 * file inside that folder, the constructor creates a ParseTree and puts in inside the list parseTrees.
 */
TreeBank::TreeBank(const string& folder) {
    vector<string> files;
    for (const auto & file : directory_iterator(folder)) {
        if (!file.is_directory()) {
            files.emplace_back(file.path());
        }
    }
    sort(files.begin(), files.end());
    for (const string& file : files) {
        auto* parseTree = new ParseTree(file);
        parseTree->setName(file.substr(file.find_last_of('/') + 1));
        parseTrees.push_back(parseTree);
    }
}

TreeBank::~TreeBank() {
    for (ParseTree* tree : parseTrees){
        delete tree;
    }
}

void TreeBank::removeTree(int index) {
    parseTrees.erase(parseTrees.begin() + index);
}
