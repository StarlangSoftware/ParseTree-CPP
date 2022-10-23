//
// Created by Olcay Taner YILDIZ on 2019-04-21.
//

#ifndef PARSETREE_PARSENODE_H
#define PARSETREE_PARSENODE_H

#include <vector>
#include "Symbol.h"
#include "SearchDirectionType.h"
#include "ConstituentSpan.h"

using namespace std;

class ParseNode {
private:
    static const vector<string> ADJP;
    static const vector<string> ADVP;
    static const vector<string> CONJP;
    static const vector<string> FRAG;
    static const vector<string> INTJ;
    static const vector<string> LST;
    static const vector<string> NAC;
    static const vector<string> PP;
    static const vector<string> PRN;
    static const vector<string> PRT;
    static const vector<string> QP;
    static const vector<string> RRC;
    static const vector<string> S;
    static const vector<string> SBAR;
    static const vector<string> SBARQ;
    static const vector<string> SINV;
    static const vector<string> SQ;
    static const vector<string> UCP;
    static const vector<string> VP;
    static const vector<string> WHADJP;
    static const vector<string> WHADVP;
    static const vector<string> WHNP;
    static const vector<string> WHPP;
    static const vector<string> NP1;
    static const vector<string> NP2;
    static const vector<string> NP3;
    static const vector<string> NP4;
    static const vector<string> NP5;
    ParseNode* searchHeadChild(const vector<string>& priorityList, SearchDirectionType direction, bool defaultCase) const;
protected:
    vector<ParseNode*> children;
    ParseNode* parent = nullptr;
    Symbol data = Symbol("");
public:
    ParseNode() = default;
    ~ParseNode();
    ParseNode(ParseNode* parent, const string& line, bool isLeaf);
    ParseNode(ParseNode* left, ParseNode* right, const Symbol& data);
    ParseNode(ParseNode* left, const Symbol& data);
    explicit ParseNode(const Symbol& data);
    ParseNode* headLeaf();
    ParseNode* headChild() const;
    vector<ParseNode*>::iterator getChildIterator();
    void addChild(ParseNode* child);
    void correctParents();
    void removeXNodes();
    void addChild(int index, ParseNode* child);
    void setChild(int index, ParseNode* child);
    void removeChild(ParseNode* child);
    int leafCount() const;
    int nodeCount() const;
    int nodeCountWithMultipleChildren() const;
    void stripPunctuation();
    int numberOfChildren() const;
    ParseNode* getChild(int i) const;
    ParseNode* firstChild() const;
    ParseNode* lastChild() const;
    bool isLastChild(ParseNode* child) const;
    int getChildIndex(ParseNode* child) const;
    bool isDescendant(ParseNode* node) const;
    ParseNode* previousSibling() const;
    ParseNode* nextSibling() const;
    ParseNode* getParent() const;
    Symbol getData() const;
    void setData(const Symbol& _data);
    int wordCount(bool excludeStopWords) const;
    void constituentSpanList(int startIndex, vector<ConstituentSpan>& list) const;
    bool isLeaf() const;
    bool isDummyNode() const;
    string toSentence() const;
    string to_string() const;
    void moveLeft(ParseNode* node);
    string ancestorString() const;
    void moveRight(ParseNode* node);
};


#endif //PARSETREE_PARSENODE_H
