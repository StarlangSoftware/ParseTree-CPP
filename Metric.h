//
// Created by Oğuz Kerem Yıldız on 21.05.2022.
//

#ifndef PARSETREE_METRIC_H
#define PARSETREE_METRIC_H
#include "vector"
#include "ParallelTreeBank.h"

using namespace std;

class Metric {
protected:
    virtual vector<double> add(ParseTree* goldTree, ParseTree* computedTree) = 0;
public:
    virtual ~Metric() {}
    virtual vector<vector<double>> calculate(ParallelTreeBank* treeBank) = 0;
    virtual vector<double> average(vector<vector<double>> matrix) = 0;
};

#endif //PARSETREE_METRIC_H
