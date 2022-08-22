//
// Created by Oğuz Kerem Yıldız on 22.05.2022.
//

#include "LeafAncestorMetric.h"

vector<ParseNode*> LeafAncestorMetric::createList(ParseNode* node) {
    vector<ParseNode*> list = vector<ParseNode*>();
    ParseNode* current = node->getParent()->getParent();
    pair<int, string> entry = pair<int, string>(-1, "");
    if (current->getChild(0) == node->getParent()) {
        entry = pair<int, string>(1, "[");
    } else if (current->getChild(current->numberOfChildren() - 1) == node->getParent()) {
        entry = pair<int, string>(1, "]");
    }
    while (current != nullptr) {
        list.push_back(current);
        current = current->getParent();
        if (current != nullptr) {
            if (entry.second == "[") {
                if (list.at(list.size() - 1) == current->getChild(0)) {
                    entry = pair<int, string>(list.size() + 1, "[");
                } else {
                    list.push_back(new ParseNode(Symbol("[")));
                    entry = pair<int, string>(-1, "");
                }
            } else if (entry.second == "]") {
                if (list.at(list.size() - 1) == current->getChild(current->numberOfChildren() - 1)) {
                    entry = pair<int, string>(list.size() + 1, "]");
                } else {
                    list.push_back(new ParseNode(Symbol("]")));
                    entry = pair<int, string>(-1, "");
                }
            }
        }
    }
    if (entry.first > -1) {
        list.insert(list.begin() + entry.first, new ParseNode(Symbol(entry.second)));
    }
    return list;
}

unordered_map<int, vector<ParseNode*>> LeafAncestorMetric::calculateStrings(ParseNode *node) {
    unordered_map<int, vector<ParseNode*>> map = unordered_map<int, vector<ParseNode*>>();
    NodeCollector collector = NodeCollector(node, new IsLeaf());
    vector<ParseNode*> nodes = collector.collect();
    for (int i = 0; i < nodes.size(); i++) {
        map[i] = createList(nodes.at(i));
    }
    return map;
}

vector<double> LeafAncestorMetric::add(ParseTree* goldTree, ParseTree* computedTree) {
    vector<double> accuracy = vector<double>(2);
    unordered_map<int, vector<ParseNode*>> map1 = calculateStrings(goldTree->getRoot());
    unordered_map<int, vector<ParseNode*>> map2 = calculateStrings(computedTree->getRoot());
    for (auto & entry : map1) {
        vector<vector<double>> dp = vector<vector<double>>(entry.second.size() + 1, vector<double>(map2[entry.first].size() + 1));
        for (int i = 0; i < entry.second.size() + 1; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i < map2[entry.first].size() + 1; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i < dp.size(); i++) {
            for (int j = 1; j < dp[i].size(); j++) {
                dp[i][j] = INFINITY;
                string string1 = entry.second.at(i - 1)->getData().getName(), string2 = map2[entry.first].at(j - 1)->getData().getName();
                if (string1.find("-PRI") != string::npos) {
                    string1 = string1.substr(0, string1.length() - 4);
                }
                if (string1 == string2) {
                    dp[i][j] = min(1 + min(dp[i][j - 1], dp[i - 1][j]), min(dp[i][j], dp[i - 1][j - 1]));
                } else {
                    dp[i][j] = min(1 + min(dp[i][j - 1], dp[i - 1][j]), min(dp[i][j], dp[i - 1][j - 1] + 1));
                }
            }
        }
        accuracy[0] += ((double) (entry.second.size() + map2[entry.first].size()) - dp[entry.second.size() - 1][map2[entry.first].size() - 1]) / (entry.second.size() + map2[entry.first].size());
    }
    accuracy[1] += map1.size();
    return accuracy;
}

vector<vector<double>> LeafAncestorMetric::calculate(ParallelTreeBank *treeBank) {
    vector<vector<double>> matrix = vector<vector<double>>(treeBank->size(), vector<double>(2));
    for (int i = 0; i < treeBank->size(); i++) {
        matrix[i] = add(treeBank->fromTree(i), treeBank->toTree(i));
    }
    return matrix;
}

vector<double> LeafAncestorMetric::average(vector<vector<double>> matrix) {
    vector<double> average = vector<double>(2);
    for (vector doubles : matrix) {
        average[0] += doubles[0];
        average[1] += doubles[1];
    }
    return average;
}
