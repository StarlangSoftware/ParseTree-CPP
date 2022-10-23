//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#ifndef PARSETREE_NODECOLLECTOR_H
#define PARSETREE_NODECOLLECTOR_H


#include "NodeCondition/NodeCondition.h"

class NodeCollector {
private:
    NodeCondition* condition;
    ParseNode* rootNode;
    void collectNodes(ParseNode* parseNode, vector<ParseNode*>& collected) const;
public:
    NodeCollector(ParseNode* rootNode, NodeCondition* condition);
    vector<ParseNode*> collect() const;
};


#endif //PARSETREE_NODECOLLECTOR_H
