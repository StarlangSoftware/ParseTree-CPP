//
// Created by Olcay Taner YILDIZ on 2019-04-21.
//

#ifndef PARSETREE_PARSENODE_H
#define PARSETREE_PARSENODE_H

#include <vector>
#include "Symbol.h"
#include "SearchDirectionType.h"

using namespace std;

class ParseNode {
private:
    vector<string> ADJP = {"NNS", "QP", "NN", "$", "ADVP", "JJ", "VBN", "VBG", "ADJP", "JJR", "NP", "JJS", "DT", "FW", "RBR", "RBS", "SBAR", "RB"};
    vector<string> ADVP = {"RB", "RBR", "RBS", "FW", "ADVP", "TO", "CD", "JJR", "JJ", "IN", "NP", "JJS", "NN"};
    vector<string> CONJP = {"CC", "RB", "IN"};
    vector<string> FRAG = {};
    vector<string> INTJ = {};
    vector<string> LST = {"LS", ":"};
    vector<string> NAC = {"NN", "NNS", "NNP", "NNPS", "NP", "NAC", "EX", "$", "CD", "QP", "PRP", "VBG", "JJ", "JJS", "JJR", "ADJP", "FW"};
    vector<string> PP = {"IN", "TO", "VBG", "VBN", "RP", "FW"};
    vector<string> PRN = {};
    vector<string> PRT = {"RP"};
    vector<string> QP = {"$", "IN", "NNS", "NN", "JJ", "RB", "DT", "CD", "NCD", "QP", "JJR", "JJS"};
    vector<string> RRC = {"VP", "NP", "ADVP", "ADJP", "PP"};
    vector<string> S = {"TO", "IN", "VP", "S", "SBAR", "ADJP", "UCP", "NP"};
    vector<string> SBAR = {"WHNP", "WHPP", "WHADVP", "WHADJP", "IN", "DT", "S", "SQ", "SINV", "SBAR", "FRAG"};
    vector<string> SBARQ = {"SQ", "S", "SINV", "SBARQ", "FRAG"};
    vector<string> SINV = {"VBZ", "VBD", "VBP", "VB", "MD", "VP", "S", "SINV", "ADJP", "NP"};
    vector<string> SQ = {"VBZ", "VBD", "VBP", "VB", "MD", "VP", "SQ"};
    vector<string> UCP = {};
    vector<string> VP = {"TO", "VBD", "VBN", "MD", "VBZ", "VB", "VBG", "VBP", "VP", "ADJP", "NN", "NNS", "NP"};
    vector<string> WHADJP = {"CC", "WRB", "JJ", "ADJP"};
    vector<string> WHADVP = {"CC", "WRB"};
    vector<string> WHNP = {"WDT", "WP", "WP$", "WHADJP", "WHPP", "WHNP"};
    vector<string> WHPP = {"IN", "TO", "FW"};
    vector<string> NP1 = {"NN", "NNP", "NNPS", "NNS", "NX", "POS", "JJR"};
    vector<string> NP2 = {"NP"};
    vector<string> NP3 = {"$", "ADJP", "PRN"};
    vector<string> NP4 = {"CD"};
    vector<string> NP5 = {"JJ" , "JJS", "RB", "QP"};
    ParseNode* searchHeadChild(vector<string> priorityList, SearchDirectionType direction, bool defaultCase);
protected:
    vector<ParseNode*> children;
    ParseNode* parent = nullptr;
    int childIndex = -1;
    Symbol data = Symbol("");
public:
    ParseNode() = default;
    ~ParseNode();
    ParseNode(ParseNode* parent, string line, bool isLeaf);
    ParseNode(ParseNode* left, ParseNode* right, Symbol data);
    ParseNode(ParseNode* left, Symbol data);
    explicit ParseNode(Symbol data);
    ParseNode* headLeaf();
    ParseNode* headChild();
    vector<ParseNode*>::iterator getChildIterator();
    void addChild(ParseNode* child);
    void correctParents();
    void removeXNodes();
    void addChild(int index, ParseNode* child);
    void setChild(int index, ParseNode* child);
    void removeChild(ParseNode* child);
    int leafCount();
    int nodeCount();
    int nodeCountWithMultipleChildren();
    void stripPunctuation();
    int numberOfChildren();
    ParseNode* getChild(int i);
    ParseNode* firstChild();
    ParseNode* lastChild();
    bool isLastChild(ParseNode* child);
    ParseNode* previousSibling();
    ParseNode* nextSibling();
    ParseNode* getParent();
    Symbol getData();
    void setData(Symbol data);
    int wordCount(bool excludeStopWords);
    bool isLeaf();
    bool isDummyNode();
    string toSentence();
    string to_string();
    void moveLeft(ParseNode* node);
    string ancestorString();
    void moveRight(ParseNode* node);
};


#endif //PARSETREE_PARSENODE_H
