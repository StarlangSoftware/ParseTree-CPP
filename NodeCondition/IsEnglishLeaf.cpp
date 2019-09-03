//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include "IsEnglishLeaf.h"

/**
 * Implemented node condition for English leaf node.
 * @param parseNode Checked node.
 * @return If the node is a leaf node and is not a dummy node, returns true; false otherwise.
 */
bool IsEnglishLeaf::satisfies(ParseNode *parseNode) {
    if (IsLeaf::satisfies(parseNode)) {
        string data = parseNode->getData().getName();
        string parentData = parseNode->getParent()->getData().getName();
        if (data.find('*') != string::npos || (data == "0" && parentData == "-NONE-")){
            return false;
        }
        return true;
    }
    return false;
}
