//
// Created by Olcay Taner YILDIZ on 2019-04-23.
//

#ifndef PARSETREE_TREEBANK_H
#define PARSETREE_TREEBANK_H


#include "ParseTree.h"

class TreeBank {
protected:
    vector<ParseTree*> parseTrees;
public:
    TreeBank() = default;
    ~TreeBank();
    TreeBank(const string& folder);
    void stripPunctuation();
    int size() const;
    int wordCount(bool excludeStopWords) const;
    ParseTree* get(int index) const;
    void removeTree(int index);
};


#endif //PARSETREE_TREEBANK_H
