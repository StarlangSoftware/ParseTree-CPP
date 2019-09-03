//
// Created by Olcay Taner YILDIZ on 2019-04-21.
//

#include "ParseNode.h"

const vector<string> ParseNode::ADJP = {"NNS", "QP", "NN", "$", "ADVP", "JJ", "VBN", "VBG", "ADJP", "JJR", "NP", "JJS", "DT", "FW", "RBR", "RBS", "SBAR", "RB"};
const vector<string> ParseNode::ADVP = {"RB", "RBR", "RBS", "FW", "ADVP", "TO", "CD", "JJR", "JJ", "IN", "NP", "JJS", "NN"};
const vector<string> ParseNode::CONJP = {"CC", "RB", "IN"};
const vector<string> ParseNode::FRAG = {};
const vector<string> ParseNode::INTJ = {};
const vector<string> ParseNode::LST = {"LS", ":"};
const vector<string> ParseNode::NAC = {"NN", "NNS", "NNP", "NNPS", "NP", "NAC", "EX", "$", "CD", "QP", "PRP", "VBG", "JJ", "JJS", "JJR", "ADJP", "FW"};
const vector<string> ParseNode::PP = {"IN", "TO", "VBG", "VBN", "RP", "FW"};
const vector<string> ParseNode::PRN = {};
const vector<string> ParseNode::PRT = {"RP"};
const vector<string> ParseNode::QP = {"$", "IN", "NNS", "NN", "JJ", "RB", "DT", "CD", "NCD", "QP", "JJR", "JJS"};
const vector<string> ParseNode::RRC = {"VP", "NP", "ADVP", "ADJP", "PP"};
const vector<string> ParseNode::S = {"TO", "IN", "VP", "S", "SBAR", "ADJP", "UCP", "NP"};
const vector<string> ParseNode::SBAR = {"WHNP", "WHPP", "WHADVP", "WHADJP", "IN", "DT", "S", "SQ", "SINV", "SBAR", "FRAG"};
const vector<string> ParseNode::SBARQ = {"SQ", "S", "SINV", "SBARQ", "FRAG"};
const vector<string> ParseNode::SINV = {"VBZ", "VBD", "VBP", "VB", "MD", "VP", "S", "SINV", "ADJP", "NP"};
const vector<string> ParseNode::SQ = {"VBZ", "VBD", "VBP", "VB", "MD", "VP", "SQ"};
const vector<string> ParseNode::UCP = {};
const vector<string> ParseNode::VP = {"TO", "VBD", "VBN", "MD", "VBZ", "VB", "VBG", "VBP", "VP", "ADJP", "NN", "NNS", "NP"};
const vector<string> ParseNode::WHADJP = {"CC", "WRB", "JJ", "ADJP"};
const vector<string> ParseNode::WHADVP = {"CC", "WRB"};
const vector<string> ParseNode::WHNP = {"WDT", "WP", "WP$", "WHADJP", "WHPP", "WHNP"};
const vector<string> ParseNode::WHPP = {"IN", "TO", "FW"};
const vector<string> ParseNode::NP1 = {"NN", "NNP", "NNPS", "NNS", "NX", "POS", "JJR"};
const vector<string> ParseNode::NP2 = {"NP"};
const vector<string> ParseNode::NP3 = {"$", "ADJP", "PRN"};
const vector<string> ParseNode::NP4 = {"CD"};
const vector<string> ParseNode::NP5 = {"JJ" , "JJS", "RB", "QP"};

ParseNode::~ParseNode(){
    for (ParseNode* child : children){
        delete child;
    }
}

/**
 * Constructs a ParseNode from a single line. If the node is a leaf node, it only sets the data. Otherwise, splits
 * the line w.r.t. spaces and paranthesis and calls itself resursively to generate its child parseNodes.
 * @param parent The parent node of this node.
 * @param line The input line to create this parseNode.
 * @param isLeaf True, if this node is a leaf node; false otherwise.
 */
ParseNode::ParseNode(ParseNode *parent, string line, bool isLeaf) {
    int parenthesisCount = 0;
    string childLine;
    this->parent = parent;
    if (parent != nullptr){
        this->childIndex = parent->children.size() - 1;
    }
    if (isLeaf){
        data = Symbol(line);
    } else {
        data = Symbol(line.substr(1, line.find(' ') - 1));
        if (line.find(')') == line.find_last_of(')')){
            children.push_back(new ParseNode(this, line.substr(line.find(' ') + 1, line.find(')') - line.find(' ') - 1), true));
        } else {
            for (int i = line.find(" ") + 1; i < line.size(); i++){
                if (line[i] != ' ' || parenthesisCount > 0){
                    childLine += line[i];
                }
                if (line[i] == '('){
                    parenthesisCount++;
                } else {
                    if (line[i] == ')'){
                        parenthesisCount--;
                    }
                }
                if (parenthesisCount == 0 && !childLine.empty()){
                    children.push_back(new ParseNode(this, Word::trim(childLine), false));
                    childLine = "";
                }
            }
        }
    }
}

/**
 * Another simple constructor for ParseNode. It takes inputs left and right children of this node, and the data.
 * Sets the corresponding attributes with these inputs.
 * @param left Left child of this node.
 * @param right Right child of this node.
 * @param data Data for this node.
 */
ParseNode::ParseNode(ParseNode *left, ParseNode* right, Symbol data) {
    children.push_back(left);
    left->parent = this;
    children.push_back(right);
    right->parent = this;
    this->data = move(data);
}

/**
 * Another simple constructor for ParseNode. It takes inputs left child of this node and the data.
 * Sets the corresponding attributes with these inputs.
 * @param left Left child of this node.
 * @param data Data for this node.
 */
ParseNode::ParseNode(ParseNode *left, Symbol data) {
    children.push_back(left);
    left->parent = this;
    this->data = move(data);
}

/**
 * Another simple constructor for ParseNode. It only take input the data, and sets it.
 * @param data Data for this node.
 */
ParseNode::ParseNode(Symbol data) {
    this->data = move(data);
}

/**
 * Extracts the head of the children of this current node.
 * @param priorityList Depending on the pos of current node, the priorities among the children are given with this parameter
 * @param direction Depending on the pos of the current node, search direction is either from left to right, or from
 *                  right to left.
 * @param defaultCase If true, and no child appears in the priority list, returns first child on the left, or first
 *                    child on the right depending on the search direction.
 * @return Head node of the children of the current node
 */
ParseNode *ParseNode::searchHeadChild(vector<string> priorityList, SearchDirectionType direction, bool defaultCase) {
    switch (direction){
        case SearchDirectionType::LEFT:
            for (const string &item : priorityList) {
                for (ParseNode* child : children) {
                    if (child->getData().trimSymbol().getName() == item) {
                        return child;
                    }
                }
            }
            if (defaultCase){
                return firstChild();
            }
            break;
        case SearchDirectionType::RIGHT:
            for (const string &item : priorityList) {
                for (int j = children.size() - 1; j >= 0; j--) {
                    ParseNode* child = children.at(j);
                    if (child->getData().trimSymbol().getName() == item) {
                        return child;
                    }
                }
            }
            if (defaultCase){
                return lastChild();
            }
    }
    return nullptr;
}

/**
 * If current node is not a leaf, it has one or more children, this method determines recursively the head of
 * that (those) child(ren). Otherwise, it returns itself. In this way, this method returns the head of all leaf
 * successors.
 * @return Head node of the descendant leaves of this current node.
 */
ParseNode *ParseNode::headLeaf() {
    if (children.size() > 0){
        ParseNode* head = headChild();
        if (head != nullptr){
            return head->headLeaf();
        } else {
            return nullptr;
        }
    } else {
        return this;
    }
}

/**
 * Calls searchHeadChild to determine the head node of all children of this current node. The search direction and
 * the search priority list is determined according to the symbol in this current parent node.
 * @return Head node among its children of this current node.
 */
ParseNode *ParseNode::headChild() {
    ParseNode* result;
    string headSymbol = data.trimSymbol().to_string();
    if (headSymbol == "ADJP") {
        return searchHeadChild(ADJP, SearchDirectionType::LEFT, true);
    } else {
        if (headSymbol == "ADVP") {
            return searchHeadChild(ADVP, SearchDirectionType::RIGHT, true);
        } else {
            if (headSymbol == "CONJP") {
                return searchHeadChild(CONJP, SearchDirectionType::RIGHT, true);
            } else {
                if (headSymbol == "FRAG") {
                    return searchHeadChild(FRAG, SearchDirectionType::RIGHT, true);
                } else {
                    if (headSymbol == "INTJ"){
                        return searchHeadChild(INTJ, SearchDirectionType::LEFT, true);
                    } else {
                        if (headSymbol == "LST"){
                            return searchHeadChild(LST, SearchDirectionType::RIGHT, true);
                        } else {
                            if (headSymbol == "NAC"){
                                return searchHeadChild(NAC, SearchDirectionType::LEFT, true);
                            } else {
                                if (headSymbol == "PP"){
                                    return searchHeadChild(PP, SearchDirectionType::RIGHT, true);
                                } else {
                                    if (headSymbol == "PRN"){
                                        return searchHeadChild(PRN, SearchDirectionType::LEFT, true);
                                    } else {
                                        if (headSymbol == "PRT"){
                                            return searchHeadChild(PRT, SearchDirectionType::RIGHT, true);
                                        } else {
                                            if (headSymbol == "QP"){
                                                return searchHeadChild(QP, SearchDirectionType::LEFT, true);
                                            } else {
                                                if (headSymbol == "RRC"){
                                                    return searchHeadChild(RRC, SearchDirectionType::RIGHT, true);
                                                } else {
                                                    if (headSymbol == "S"){
                                                        return searchHeadChild(S, SearchDirectionType::LEFT, true);
                                                    } else {
                                                        if (headSymbol == "SBAR"){
                                                            return searchHeadChild(SBAR, SearchDirectionType::LEFT, true);
                                                        } else {
                                                            if (headSymbol == "SBARQ"){
                                                                return searchHeadChild(SBARQ, SearchDirectionType::LEFT, true);
                                                            } else {
                                                                if (headSymbol == "SINV"){
                                                                    return searchHeadChild(SINV, SearchDirectionType::LEFT, true);
                                                                } else {
                                                                    if (headSymbol == "SQ"){
                                                                        return searchHeadChild(SQ, SearchDirectionType::LEFT, true);
                                                                    } else {
                                                                        if (headSymbol == "UCP"){
                                                                            return searchHeadChild(UCP, SearchDirectionType::RIGHT, true);
                                                                        } else {
                                                                            if (headSymbol == "VP"){
                                                                                return searchHeadChild(VP, SearchDirectionType::LEFT, true);
                                                                            } else {
                                                                                if (headSymbol == "WHADJP"){
                                                                                    return searchHeadChild(WHADJP, SearchDirectionType::LEFT, true);
                                                                                } else {
                                                                                    if (headSymbol == "WHADVP"){
                                                                                        return searchHeadChild(WHADVP, SearchDirectionType::RIGHT, true);
                                                                                    } else {
                                                                                        if (headSymbol == "WHNP"){
                                                                                            return searchHeadChild(WHNP, SearchDirectionType::LEFT, true);
                                                                                        } else {
                                                                                            if (headSymbol == "WHPP"){
                                                                                                return searchHeadChild(WHPP, SearchDirectionType::RIGHT, true);
                                                                                            } else {
                                                                                                if (headSymbol == "NP"){
                                                                                                    if (lastChild()->getData().getName() == "POS"){
                                                                                                        return lastChild();
                                                                                                    } else {
                                                                                                        result = searchHeadChild(NP1, SearchDirectionType::RIGHT, false);
                                                                                                        if (result != nullptr){
                                                                                                            return result;
                                                                                                        } else {
                                                                                                            result = searchHeadChild(NP2, SearchDirectionType::LEFT, false);
                                                                                                            if (result != nullptr){
                                                                                                                return result;
                                                                                                            } else {
                                                                                                                result = searchHeadChild(NP3, SearchDirectionType::RIGHT, false);
                                                                                                                if (result != nullptr){
                                                                                                                    return result;
                                                                                                                } else {
                                                                                                                    result = searchHeadChild(NP4, SearchDirectionType::RIGHT, false);
                                                                                                                    if (result != nullptr){
                                                                                                                        return result;
                                                                                                                    } else {
                                                                                                                        result = searchHeadChild(NP5, SearchDirectionType::RIGHT, false);
                                                                                                                        if (result != nullptr){
                                                                                                                            return  result;
                                                                                                                        } else {
                                                                                                                            return lastChild();
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

/**
 * Returns an iterator for the child nodes of this {@link ParseNode}.
 * @return Iterator for the children of thid very node.
 */
vector<ParseNode *>::iterator ParseNode::getChildIterator() {
    return children.begin();
}

/**
 * Adds a child node at the end of the children node list.
 * @param child Child node to be added.
 */
void ParseNode::addChild(ParseNode* child) {
    children.push_back(child);
    child->parent = this;
}

/**
 * Recursive method to restore the parents of all nodes below this node in the hierarchy.
 */
void ParseNode::correctParents() {
    for (ParseNode* child : children){
        child->parent = this;
        child->correctParents();
    }
}

/**
 * Recursive method to remove all nodes starting with the symbol X. If the node is removed, its children are
 * connected to the next sibling of the deleted node.
 */
void ParseNode::removeXNodes() {
    int i = 0;
    while (i < children.size()){
        if (Word::startsWith(children.at(i)->getData().getName(), "X")){
            children.insert(children.begin() + i + 1, children.at(i)->children.begin(), children.at(i)->children.end());
            children.erase(children.begin() + i);
        } else {
            i++;
        }
    }
    for (ParseNode* child:children){
        child->removeXNodes();
    }
}

/**
 * Adds a child node at the given specific index in the children node list.
 * @param index Index where the new child node will be added.
 * @param child Child node to be added.
 */
void ParseNode::addChild(int index, ParseNode* child) {
    children.insert(children.begin() + index, child);
    child->parent = this;
}

/**
 * Replaces a child node at the given specific with a new child node.
 * @param index Index where the new child node replaces the old one.
 * @param child Child node to be replaced.
 */
void ParseNode::setChild(int index, ParseNode *child) {
    children[index] = child;
}

/**
 * Removes a given child from children node list.
 * @param child Child node to be deleted.
 */
void ParseNode::removeChild(ParseNode* child) {
    for (int i = 0; i < children.size(); i++){
        if (children.at(i) == child){
            children.erase(children.begin() + i);
            break;
        }
    }
}

/**
 * Recursive method to calculate the number of all leaf nodes in the subtree rooted with this current node.
 * @return Number of all leaf nodes in the current subtree.
 */
int ParseNode::leafCount() {
    if (children.empty()){
        return 1;
    } else {
        int sum = 0;
        for (ParseNode* child : children) {
            sum += child->leafCount();
        }
        return sum;
    }
}

/**
 * Recursive method to calculate the number of all nodes in the subtree rooted with this current node.
 * @return Number of all nodes in the current subtree.
 */
int ParseNode::nodeCount() {
    if (children.empty()){
        int sum = 1;
        for (ParseNode* child: children){
            sum += child->nodeCount();
        }
        return sum;
    } else {
        return 1;
    }
}

/**
 * Recursive method to calculate the number of all nodes, which have more than one children, in the subtree rooted
 * with this current node.
 * @return Number of all nodes, which have more than one children, in the current subtree.
 */
int ParseNode::nodeCountWithMultipleChildren() {
    if (children.size() > 1){
        int sum = 1;
        for (ParseNode* child: children){
            sum += child->nodeCountWithMultipleChildren();
        }
        return sum;
    } else {
        return 0;
    }
}

/**
 * Recursive method to remove all punctuation nodes from the current subtree.
 */
void ParseNode::stripPunctuation() {
    auto iterator = children.begin();
    while (iterator != children.end()){
        if (Word::isPunctuation((*iterator)->getData().getName())){
            iterator = children.erase(iterator);
        } else {
            iterator++;
        }
    }
    for (ParseNode* node: children)
        node->stripPunctuation();
}

/**
 * Returns number of children of this node.
 * @return Number of children of this node.
 */
int ParseNode::numberOfChildren() {
    return children.size();
}

/**
 * Returns the i'th child of this node.
 * @param i Index of the retrieved node.
 * @return i'th child of this node.
 */
ParseNode *ParseNode::getChild(int i) {
    return children.at(i);
}

/**
 * Returns the first child of this node.
 * @return First child of this node.
 */
ParseNode *ParseNode::firstChild() {
    return children.at(0);
}

/**
 * Returns the last child of this node.
 * @return Last child of this node.
 */
ParseNode *ParseNode::lastChild() {
    return children.at(children.size() - 1);
}

/**
 * Checks if the given node is the last child of this node.
 * @param child To be checked node.
 * @return True, if child is the last child of this node, false otherwise.
 */
bool ParseNode::isLastChild(ParseNode *child) {
    return children.at(children.size() - 1) == child;
}

/**
 * Returns the previous sibling (sister) of this node.
 * @return If this is the first child of its parent, returns null. Otherwise, returns the previous sibling of this
 * node.
 */
ParseNode *ParseNode::previousSibling() {
    for (int i = 1; i < parent->children.size(); i++){
        if (parent->children.at(i) == this){
            return parent->children.at(i - 1);
        }
    }
    return nullptr;
}

/**
 * Returns the next sibling (sister) of this node.
 * @return If this is the last child of its parent, returns null. Otherwise, returns the next sibling of this
 * node.
 */
ParseNode *ParseNode::nextSibling() {
    for (int i = 0; i < parent->children.size() - 1; i++){
        if (parent->children.at(i) == this){
            return parent->children.at(i + 1);
        }
    }
    return nullptr;
}

/**
 * Accessor for the parent attribute.
 * @return Parent of this node.
 */
ParseNode *ParseNode::getParent() {
    return parent;
}

/**
 * Accessor for the data attribute.
 * @return Data of this node.
 */
Symbol ParseNode::getData() {
    return data;
}

/**
 * Mutator of the data attribute.
 * @param data Data to be set.
 */
void ParseNode::setData(Symbol data) {
    this->data = move(data);
}

/**
 * Recursive function to count the number of words in the subtree rooted at this node.
 * @param excludeStopWords If true, stop words are not counted.
 * @return Number of words in the subtree rooted at this node.
 */
int ParseNode::wordCount(bool excludeStopWords) {
    int sum;
    if (children.empty()){
        if (!excludeStopWords){
            sum = 1;
        } else {
            if (data.getName() == "," || data.getName() == "." || data.getName() == ";"
                || data.getName().find('*') != string::npos || data.getName() == "at" || data.getName() == "the"
                || data.getName() == "to" || data.getName() == "a" || data.getName() == "an"
                || data.getName() == "not" || data.getName() == "is" || data.getName() == "was"
                || data.getName() == "were" || data.getName() == "have" || data.getName() == "had"
                || data.getName() == "has" || data.getName() == "!" || data.getName() == "?"
                || data.getName() == "by" || data.getName() == "at" || data.getName() == "on"
                || data.getName() == "off" || data.getName() == "'s" || data.getName() == "n't"
                || data.getName() == "can" || data.getName() == "could" || data.getName() == "may"
                || data.getName() == "might" || data.getName() == "will" || data.getName() == "would"
                || data.getName() == "''" || data.getName() == "'" || data.getName() == "\""
                || data.getName() == "\"\"" || data.getName() == "as" || data.getName() == "with"
                || data.getName() == "for" || data.getName() == "will" || data.getName() == "would"
                || data.getName() == "than" || data.getName() == "``" || data.getName() == "$"
                || data.getName() == "and" || data.getName() == "or" || data.getName() == "of"
                || data.getName() == "are" || data.getName() == "be" || data.getName() == "been"
                || data.getName() == "do" || data.getName() == "few" || data.getName() == "there"
                || data.getName() == "up" || data.getName() == "down") {
                sum = 0;
            } else {
                sum = 1;
            }
        }
    }
    else{
        sum = 0;
    }
    for (ParseNode* aChild : children) {
        sum += aChild->wordCount(excludeStopWords);
    }
    return sum;
}

/**
 * Returns true if this node is leaf, false otherwise.
 * @return true if this node is leaf, false otherwise.
 */
bool ParseNode::isLeaf() {
    return children.empty();
}

/**
 * Returns true if this node does not contain a meaningful data, false otherwise.
 * @return true if this node does not contain a meaningful data, false otherwise.
 */
bool ParseNode::isDummyNode() {
    return getData().getName().find('*') != string::npos || (getData().getName() == "0" && parent->getData().getName() == "-NONE-");
}

/**
 * Recursive function to convert the subtree rooted at this node to a sentence.
 * @return A sentence which contains all words in the subtree rooted at this node.
 */
string ParseNode::toSentence() {
    if (children.empty()){
        if (!getData().getName().empty() && !isDummyNode()){
            return " " + Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(Word::replaceAll(getData().getName(), "-LRB-", "("), "-RRB-", ")"), "-LSB-", "["), "-RSB-", "]"), "-LCB-", "{"), "-RCB-", "}"), "-lrb-", "("), "-rrb-", ")"), "-lsb-", "["), "-rsb-", "]"), "-lcb-", "{"), "-rcb-", "}");
        } else {
            return " ";
        }
    } else {
        string st;
        for (ParseNode* aChild : children) {
            st += aChild->toSentence();
        }
        return st;
    }
}

/**
 * Recursive function to convert the subtree rooted at this node to a string.
 * @return A string which contains all words in the subtree rooted at this node.
 */
string ParseNode::to_string() {
    if (children.size() < 2){
        if (children.empty()){
            return getData().getName();
        } else {
            return "(" + data.getName() + " " + firstChild()->to_string() + ")";
        }
    } else {
        string st = "(" + data.getName();
        for (ParseNode* aChild : children) {
            st += " " + aChild->to_string();
        }
        return st + ") ";
    }
}

/**
 * Swaps the given child node of this node with the previous sibling of that given node. If the given node is the
 * leftmost child, it swaps with the last node.
 * @param node Node to be swapped.
 */
void ParseNode::moveLeft(ParseNode *node) {
    int i;
    for (i = 0; i < children.size(); i++) {
        if (children.at(i) == node){
            if (i == 0){
                iter_swap(children.begin(), children.begin() + children.size() - 1);
            } else {
                iter_swap(children.begin() + i, children.begin() + (i - 1) % children.size());
            }
            return;
        }
    }
    for (ParseNode* aChild: children){
        aChild->moveLeft(node);
    }
}

/**
 * Recursive function to concatenate the data of the all ascendant nodes of this node to a string.
 * @return A string which contains all data of all the ascendant nodes of this node.
 */
string ParseNode::ancestorString() {
    if (parent == nullptr){
        return data.getName();
    } else {
        return parent->ancestorString() + data.getName();
    }
}

/**
 * Swaps the given child node of this node with the next sibling of that given node. If the given node is the
 * rightmost child, it swaps with the first node.
 * @param node Node to be swapped.
 */
void ParseNode::moveRight(ParseNode *node) {
    int i;
    for (i = 0; i < children.size(); i++) {
        if (children.at(i) == node){
            iter_swap(children.begin() + i, children.begin() + (i + 1) % children.size());
            return;
        }
    }
    for (ParseNode* aChild: children){
        aChild->moveRight(node);
    }
}
