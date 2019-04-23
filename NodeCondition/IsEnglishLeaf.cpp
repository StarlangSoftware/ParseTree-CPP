//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include "IsEnglishLeaf.h"

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
