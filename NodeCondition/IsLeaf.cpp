//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include "IsLeaf.h"

bool IsLeaf::satisfies(ParseNode *parseNode) {
    return parseNode->numberOfChildren() == 0;
}
