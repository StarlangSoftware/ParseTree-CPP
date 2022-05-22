//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#include "ParsevalMetric.h"

vector<double> ParsevalMetric::add(ParseTree *goldTree, ParseTree *computedTree) {
    vector<double> scores = vector<double>(3);
    unordered_set<string> set1 = unordered_set<string>();
    traverseTree(set1, 0, goldTree->getRoot());
    unordered_set<string> set2 = unordered_set<string>();
    traverseTree(set2, 0, computedTree->getRoot());
    int score = 0;
    for (const string& key : set1) {
        if (key.find("-PRI") != string::npos) {
            if (set2.find(key.substr(0, key.length() - 4)) != set2.end()) {
                score++;
            }
        } else {
            if (set2.find(key) != set2.end()) {
                score++;
            }
        }
    }
    scores[0] = (score + 0.00) / set2.size();
    scores[1] = (score + 0.00) / set1.size();
    scores[2] = (2 * scores[0] * scores[1]) / (scores[0] + scores[1]);
    return scores;
}

vector<vector<double>> ParsevalMetric::calculate(ParallelTreeBank *treeBank) {
    vector<vector<double>> matrix = vector<vector<double>>(treeBank->size(), vector<double>(3));
    for (int i = 0; i < treeBank->size(); i++) {
        matrix[i] = add(treeBank->fromTree(i), treeBank->toTree(i));
    }
    return matrix;
}

vector<double> ParsevalMetric::average(vector<vector<double>> matrix) {
    vector<double> average = vector<double>(3);
    double precision = 0, recall = 0, fScore = 0;
    for (vector<double> doubles : matrix) {
        precision += doubles[0];
        recall += doubles[1];
        fScore += doubles[2];
    }
    average[0] = (precision + 0.00) / matrix.size();
    average[1] = (recall + 0.00) / matrix.size();
    average[2] = (fScore + 0.00) / matrix.size();
    return average;
}

pair<string, int> ParsevalMetric::traverseTree(unordered_set<string>& set, int count, ParseNode *node) {
    if (node->getChild(0)->isLeaf()) {
        set.insert(to_string(count) + "|" + node->getData().getName());
        return pair{to_string(count), count + 1};
    }
    string current;
    int currentCount = count;
    for (int i = 0; i < node->numberOfChildren(); i++) {
        ParseNode* child = node->getChild(i);
        pair<string, int> entry = traverseTree(set, currentCount, child);
        current.append(entry.first);
        currentCount = entry.second;
        if (i + 1 != node->numberOfChildren()) {
            current.append("-");
        }
    }
    set.insert(current + "|" + node->getData().getName());
    return pair{current, currentCount};
}
