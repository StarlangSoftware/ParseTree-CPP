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
    void removeDifferentTrees() const;
public:
    ParallelTreeBank();
    ~ParallelTreeBank();
    ParallelTreeBank(const string& folder1, const string& folder2);
    [[nodiscard]] int size() const;
    [[nodiscard]] ParseTree* fromTree(int index) const;
    [[nodiscard]] ParseTree* toTree(int index) const;
    [[nodiscard]] TreeBank* getFromTreeBank() const;
    [[nodiscard]] TreeBank* getToTreeBank() const;
};


#endif //PARSETREE_PARALLELTREEBANK_H
