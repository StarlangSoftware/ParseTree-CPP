//
// Created by Olcay Taner YILDIZ on 12.05.2022.
//

#include "ParallelTreeBank.h"

void ParallelTreeBank::removeDifferentTrees() {
    int i, j;
    i = 0;
    j = 0;
    while (i < fromTreeBank->size() && j < toTreeBank->size()){
        if (fromTreeBank->get(i)->getName().compare(toTreeBank->get(j)->getName()) < 0){
            fromTreeBank->removeTree(i);
        } else {
            if (toTreeBank->get(j)->getName().compare(fromTreeBank->get(i)->getName()) < 0){
                toTreeBank->removeTree(j);
            } else {
                i++;
                j++;
            }
        }
    }
    while (i < fromTreeBank->size()){
        fromTreeBank->removeTree(i);
    }
    while (j < toTreeBank->size()){
        toTreeBank->removeTree(j);
    }
}

ParallelTreeBank::ParallelTreeBank(const string &folder1, const string &folder2) {
    fromTreeBank = new TreeBank(folder1);
    toTreeBank = new TreeBank(folder2);
    removeDifferentTrees();
}

int ParallelTreeBank::size() const{
    return fromTreeBank->size();
}

ParseTree *ParallelTreeBank::fromTree(int index) const{
    return fromTreeBank->get(index);
}

ParseTree *ParallelTreeBank::toTree(int index) const{
    return toTreeBank->get(index);
}

TreeBank* ParallelTreeBank::getFromTreeBank() const{
    return fromTreeBank;
}

TreeBank* ParallelTreeBank::getToTreeBank() const{
    return toTreeBank;
}

ParallelTreeBank::~ParallelTreeBank() {
    delete fromTreeBank;
    delete toTreeBank;
}

ParallelTreeBank::ParallelTreeBank() = default;
