//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#ifndef PARSETREE_ISLEAF_H
#define PARSETREE_ISLEAF_H


#include "NodeCondition.h"

class IsLeaf : public NodeCondition {
public:
    bool satisfies(ParseNode* parseNode) override;

};


#endif //PARSETREE_ISLEAF_H
