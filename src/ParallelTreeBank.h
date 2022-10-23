//
// Created by Olcay Taner YILDIZ on 12.05.2022.
//

#ifndef PARSETREE_PARALLELTREEBANK_H
#define PARSETREE_PARALLELTREEBANK_H


#include "TreeBank.h"

class ParallelTreeBank {
protected:
    TreeBank* fromTreeBank;
    TreeBank* toTreeBank;
    void removeDifferentTrees();
public:
    ParallelTreeBank();
    ~ParallelTreeBank();
    ParallelTreeBank(const string& folder1, const string& folder2);
    int size() const;
    ParseTree* fromTree(int index) const;
    ParseTree* toTree(int index) const;
    TreeBank* getFromTreeBank() const;
    TreeBank* getToTreeBank() const;
};


#endif //PARSETREE_PARALLELTREEBANK_H
