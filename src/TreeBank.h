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
    explicit TreeBank(const string& folder);
    void stripPunctuation() const;
    [[nodiscard]] int size() const;
    [[nodiscard]] int wordCount(bool excludeStopWords) const;
    [[nodiscard]] ParseTree* get(int index) const;
    void removeTree(int index);
};


#endif //PARSETREE_TREEBANK_H
