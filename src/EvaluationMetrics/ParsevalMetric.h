//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#ifndef PARSETREE_PARSEVALMETRIC_H
#define PARSETREE_PARSEVALMETRIC_H
#include "Metric.h"
#include "unordered_set"


class ParsevalMetric : public Metric {
protected:
    pair<string, int> traverseTree(unordered_set<string>& set, int count, ParseNode* node);
    vector<double> add(ParseTree* goldTree, ParseTree* computedTree) override;
public:
    vector<vector<double>> calculate(ParallelTreeBank* treeBank) override;
    vector<double> average(vector<vector<double>> matrix) override;
};


#endif //PARSETREE_PARSEVALMETRIC_H
