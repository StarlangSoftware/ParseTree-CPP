//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include "NodeCollector.h"

NodeCollector::NodeCollector(ParseNode *rootNode, NodeCondition *condition) {
    this->rootNode = rootNode;
    this->condition = condition;
}

void NodeCollector::collectNodes(ParseNode *parseNode, vector<ParseNode *> &collected) {
    if (condition->satisfies(parseNode)){
        collected.push_back(parseNode);
    } else {
        for (int i = 0; i < parseNode->numberOfChildren(); i++){
            collectNodes(parseNode->getChild(i), collected);
        }
    }
}

vector<ParseNode *> NodeCollector::collect() {
    vector<ParseNode*> result;
    collectNodes(rootNode, result);
    return result;
}
