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
    [[nodiscard]] string getName() const;
    ParseNode* nextLeafNode(const ParseNode* parseNode) const;
    ParseNode* previousLeafNode(const ParseNode* parseNode) const;
    [[nodiscard]] int nodeCountWithMultipleChildren() const;
    [[nodiscard]] int nodeCount() const;
    [[nodiscard]] int leafCount() const;
    [[nodiscard]] bool isFullSentence() const;
    [[nodiscard]] vector<ConstituentSpan> constituentSpanList() const;
    void save(const string& fileName) const;
    void correctParents() const;
    void removeXNodes() const;
    void stripPunctuation() const;
    [[nodiscard]] ParseNode* getRoot() const;
    [[nodiscard]] string toSentence() const;
    [[nodiscard]] string to_string() const;
    [[nodiscard]] int wordCount(bool excludeStopWords) const;
};


#endif //PARSETREE_PARSETREE_H
