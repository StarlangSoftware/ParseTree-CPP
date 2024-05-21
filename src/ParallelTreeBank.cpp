//
// Created by Olcay Taner YILDIZ on 12.05.2022.
//

#include "ParallelTreeBank.h"

/**
 * Given two treebanks read, the method removes the trees which do not exist in one of the treebanks. At the end,
 * we will only have the tree files that exist in both treebanks.
 */
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

/**
 * Constructor for the ParallelTreeBank class. A ParallelTreeBank consists of two treebanks, where each sentence
 * appears in both treebanks with possibly different tree structures. Each treebank is stored in a separate folder.
 * Both treebanks are read and distinct sentences are removed from the treebanks.
 * @param folder1 Folder containing the files for trees in the first treebank.
 * @param folder2 Folder containing the files for trees in the second treebank.
 */
ParallelTreeBank::ParallelTreeBank(const string &folder1, const string &folder2) {
    fromTreeBank = new TreeBank(folder1);
    toTreeBank = new TreeBank(folder2);
    removeDifferentTrees();
}

/**
 * Returns number of sentences in ParallelTreeBank.
 * @return Number of sentences.
 */
int ParallelTreeBank::size() const{
    return fromTreeBank->size();
}

/**
 * Returns the tree at position index in the first treebank.
 * @param index Position of the tree in the first treebank.
 * @return The tree at position index in the first treebank.
 */
ParseTree *ParallelTreeBank::fromTree(int index) const{
    return fromTreeBank->get(index);
}

/**
 * Returns the tree at position index in the second treebank.
 * @param index Position of the tree in the second treebank.
 * @return The tree at position index in the second treebank.
 */
ParseTree *ParallelTreeBank::toTree(int index) const{
    return toTreeBank->get(index);
}

/**
 * Returns the first treebank.
 * @return First treebank.
 */
TreeBank* ParallelTreeBank::getFromTreeBank() const{
    return fromTreeBank;
}

/**
 * Returns the second treebank.
 * @return Second treebank.
 */
TreeBank* ParallelTreeBank::getToTreeBank() const{
    return toTreeBank;
}

ParallelTreeBank::~ParallelTreeBank() {
    delete fromTreeBank;
    delete toTreeBank;
}

/**
 * Empty constructor for the parallel treebank.
 */
ParallelTreeBank::ParallelTreeBank() = default;
