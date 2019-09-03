//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include "NodeCollector.h"

/**
 * Constructor for the NodeCollector class. NodeCollector's main aim is to collect a set of ParseNode's from a
 * subtree rooted at rootNode, where the ParseNode's satisfy a given NodeCondition, which is implemented by other
 * interface class.
 * @param rootNode Root node of the subtree
 * @param condition The condition interface for which all nodes in the subtree rooted at rootNode will be checked
 */
NodeCollector::NodeCollector(ParseNode *rootNode, NodeCondition *condition) {
    this->rootNode = rootNode;
    this->condition = condition;
}

/**
 * Private recursive method to check all descendants of the parseNode, if they ever satisfy the given node condition
 * @param parseNode Root node of the subtree
 * @param collected The {@link ArrayList} where the collected ParseNode's will be stored.
 */
void NodeCollector::collectNodes(ParseNode *parseNode, vector<ParseNode *> &collected) {
    if (condition->satisfies(parseNode)){
        collected.push_back(parseNode);
    } else {
        for (int i = 0; i < parseNode->numberOfChildren(); i++){
            collectNodes(parseNode->getChild(i), collected);
        }
    }
}

/**
 * Collects and returns all ParseNode's satisfying the node condition.
 * @return All ParseNode's satisfying the node condition.
 */
vector<ParseNode *> NodeCollector::collect() {
    vector<ParseNode*> result;
    collectNodes(rootNode, result);
    return result;
}
