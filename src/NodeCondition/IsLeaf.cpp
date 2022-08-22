//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include "IsLeaf.h"

/**
 * Implemented node condition for the leaf node. If a node has no children it is a leaf node.
 * @param parseNode Checked node.
 * @return True if the input node is a leaf node, false otherwise.
 */
bool IsLeaf::satisfies(ParseNode *parseNode) {
    return parseNode->numberOfChildren() == 0;
}
