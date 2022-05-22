//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#ifndef PARSETREE_MODIFIEDLEAFANCESTORMETRIC_H
#define PARSETREE_MODIFIEDLEAFANCESTORMETRIC_H
#include "LeafAncestorMetric.h"
#include "unordered_set"

class ModifiedLeafAncestorMetric : public LeafAncestorMetric {
private:
    vector<ParseNode*> createList(ParseNode* node, unordered_set<ParseNode*> visited);
protected:
    unordered_map<int, vector<ParseNode*>> calculateStrings(ParseNode* node) override;
};


#endif //PARSETREE_MODIFIEDLEAFANCESTORMETRIC_H
