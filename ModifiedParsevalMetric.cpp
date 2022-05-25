//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#include "ModifiedParsevalMetric.h"

vector<double> ModifiedParsevalMetric::add(ParseTree *goldTree, ParseTree *computedTree) {
    vector<double> scores = vector<double>(3);
    pair<int, int> entry = find(goldTree->getRoot());
    double m = entry.first, n = entry.second;
    unordered_set<string> set1 = unordered_set<string>();
    traverseTree(set1, 0, goldTree->getRoot());
    unordered_set<string> set2 = unordered_set<string>();
    traverseTree(set2, 0, computedTree->getRoot());
    double score = 0;
    double t = ((m + n) / (m * (1 + (m / (m + n))) + n * (1 - (m / (m + n)))));
    for (const string& key : set1) {
        if (key.find("-PRI") != string::npos) {
            if (set2.find(key.substr(0, key.length() - 4)) != set2.end()) {
                score += (1 + (m / (m + n))) * t;
            }
        } else {
            if (set2.find(key) != set2.end()) {
                score += (1 - (m / (m + n))) * t;
            }
        }
    }
    scores[0] = (score + 0.00) / set2.size();
    scores[1] = (score + 0.00) / set1.size();
    scores[2] = (2 * scores[0] * scores[1]) / (scores[0] + scores[1]);
    return scores;
}

pair<int, int> ModifiedParsevalMetric::find(ParseNode *node) {
    pair<int, int> current = pair{0, 0};
    for (int i = 0; i < node->numberOfChildren(); i++) {
        if (!node->getChild(i)->isLeaf()) {
            pair<int, int> child = find(node->getChild(i));
            current = pair{current.first + child.first, current.second + child.second};
        }
    }
    if (node->getData().getName().find("-PRI") != string::npos) {
        return pair{current.first + 1, current.second};
    } else {
        return pair{current.first, current.second + 1};
    }
}
