//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#ifndef PARSETREE_PARSETREE_H
#define PARSETREE_PARSETREE_H

#include <vector>
#include <string>
#include "ParseNode.h"
#include "ConstituentSpan.h"

using namespace std;

class ParseTree {
private:
    static const vector<string> sentenceLabels;
protected:
    ParseNode* root = nullptr;
    string name;
public:
    ParseTree() = default;
    explicit ParseTree(ParseNode* root);
    explicit ParseTree(istream& inputFile);
    explicit ParseTree(const string& fileName);
    void setName(const string& _name);
    string getName() const;
    ParseNode* nextLeafNode(ParseNode* parseNode) const;
    ParseNode* previousLeafNode(ParseNode* parseNode) const;
    int nodeCountWithMultipleChildren() const;
    int nodeCount() const;
    int leafCount() const;
    bool isFullSentence() const;
    vector<ConstituentSpan> constituentSpanList() const;
    void save(const string& fileName);
    void correctParents();
    void removeXNodes();
    void stripPunctuation();
    ParseNode* getRoot() const;
    string toSentence() const;
    string to_string() const;
    int wordCount(bool excludeStopWords) const;
};


#endif //PARSETREE_PARSETREE_H
