//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#ifndef PARSETREE_NODECONDITION_H
#define PARSETREE_NODECONDITION_H

#include "../ParseNode.h"

class NodeCondition {
public:
    virtual bool satisfies(ParseNode* parseNode) = 0;
};


#endif //PARSETREE_NODECONDITION_H
