//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#ifndef PARSETREE_MODIFIEDPARSEVALMETRIC_H
#define PARSETREE_MODIFIEDPARSEVALMETRIC_H
#include "ParsevalMetric.h"


class ModifiedParsevalMetric : public ParsevalMetric {
private:
    pair<int, int> find(ParseNode* node);
protected:
    vector<double> add(ParseTree* goldTree, ParseTree* computedTree) override;
};


#endif //PARSETREE_MODIFIEDPARSEVALMETRIC_H
