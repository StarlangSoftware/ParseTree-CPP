//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#ifndef PARSETREE_LEAFANCESTORMETRIC_H
#define PARSETREE_LEAFANCESTORMETRIC_H
#include "Metric.h"
#include "unordered_map"
#include "NodeCollector.h"
#include "NodeCondition/IsLeaf.h"

class LeafAncestorMetric : public Metric {
private:
    vector<ParseNode*> createList(ParseNode* node);
protected:
    virtual unordered_map<int, vector<ParseNode*>> calculateStrings(ParseNode* node);
    vector<double> add(ParseTree* goldTree, ParseTree* computedTree) override;
public:
    vector<vector<double>> calculate(ParallelTreeBank* treeBank) override;
    vector<double> average(vector<vector<double>> matrix) override;
};


#endif //PARSETREE_LEAFANCESTORMETRIC_H
