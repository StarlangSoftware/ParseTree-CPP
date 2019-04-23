//
// Created by Olcay Taner YILDIZ on 2019-04-21.
//

#include "ParseNode.h"

ParseNode::~ParseNode(){
    for (ParseNode* child : children){
        delete child;
    }
}

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

ParseNode::ParseNode(ParseNode *left, ParseNode* right, Symbol data) {
    children.push_back(left);
    left->parent = this;
    children.push_back(right);
    right->parent = this;
    this->data = move(data);
}

ParseNode::ParseNode(ParseNode *left, Symbol data) {
    children.push_back(left);
    left->parent = this;
    this->data = move(data);
}

ParseNode::ParseNode(Symbol data) {
    this->data = move(data);
}

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

vector<ParseNode *>::iterator ParseNode::getChildIterator() {
    return children.begin();
}

void ParseNode::addChild(ParseNode* child) {
    children.push_back(child);
    child->parent = this;
}

void ParseNode::correctParents() {
    for (ParseNode* child : children){
        child->parent = this;
        child->correctParents();
    }
}

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

void ParseNode::addChild(int index, ParseNode* child) {
    children.insert(children.begin() + index, child);
    child->parent = this;
}

void ParseNode::setChild(int index, ParseNode *child) {
    children[index] = child;
}

void ParseNode::removeChild(ParseNode* child) {
    for (int i = 0; i < children.size(); i++){
        if (children.at(i) == child){
            children.erase(children.begin() + i);
            break;
        }
    }
}

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

int ParseNode::numberOfChildren() {
    return children.size();
}

ParseNode *ParseNode::getChild(int i) {
    return children.at(i);
}

ParseNode *ParseNode::firstChild() {
    return children.at(0);
}

ParseNode *ParseNode::lastChild() {
    return children.at(children.size() - 1);
}

bool ParseNode::isLastChild(ParseNode *child) {
    return children.at(children.size() - 1) == child;
}

ParseNode *ParseNode::previousSibling() {
    for (int i = 1; i < parent->children.size(); i++){
        if (parent->children.at(i) == this){
            return parent->children.at(i - 1);
        }
    }
    return nullptr;
}

ParseNode *ParseNode::nextSibling() {
    for (int i = 0; i < parent->children.size() - 1; i++){
        if (parent->children.at(i) == this){
            return parent->children.at(i + 1);
        }
    }
    return nullptr;
}

ParseNode *ParseNode::getParent() {
    return parent;
}

Symbol ParseNode::getData() {
    return data;
}

void ParseNode::setData(Symbol data) {
    this->data = move(data);
}

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

bool ParseNode::isLeaf() {
    return children.empty();
}

bool ParseNode::isDummyNode() {
    return getData().getName().find('*') != string::npos || (getData().getName() == "0" && parent->getData().getName() == "-NONE-");
}

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

string ParseNode::ancestorString() {
    if (parent == nullptr){
        return data.getName();
    } else {
        return parent->ancestorString() + data.getName();
    }
}

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
