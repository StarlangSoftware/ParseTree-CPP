//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#include "ModifiedLeafAncestorMetric.h"

vector<ParseNode *> ModifiedLeafAncestorMetric::createList(ParseNode *node, unordered_set<ParseNode *> visited) {
    vector<ParseNode*> list = vector<ParseNode*>();
    ParseNode* current = node->getParent();
    while (current != nullptr) {
        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            list.push_back(current);
        } else {
            list.push_back(new ParseNode(Symbol(".")));
        }
        current = current->getParent();
    }
    return list;
}

unordered_map<int, vector<ParseNode *>> ModifiedLeafAncestorMetric::calculateStrings(ParseNode *node) {
    unordered_set<ParseNode*> visited = unordered_set<ParseNode*>();
    unordered_map<int, vector<ParseNode*>> map = unordered_map<int, vector<ParseNode*>>();
    NodeCollector collector = NodeCollector(node, new IsLeaf());
    vector<ParseNode*> nodes = collector.collect();
    for (int i = 0; i < nodes.size(); i++) {
        map[i] = createList(nodes.at(i), visited);
    }
    return map;
}
