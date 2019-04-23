//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#ifndef PARSETREE_ISENGLISHLEAF_H
#define PARSETREE_ISENGLISHLEAF_H


#include "NodeCondition.h"
#include "IsLeaf.h"

class IsEnglishLeaf : public IsLeaf{
public:
    bool satisfies(ParseNode* parseNode) override;
};


#endif //PARSETREE_ISENGLISHLEAF_H
