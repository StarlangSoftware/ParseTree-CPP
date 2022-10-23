//
// Created by Olcay Taner YILDIZ on 2019-04-22.
//

#include <ostream>
#include <fstream>
#include "ParseTree.h"
#include "NodeCollector.h"
#include "NodeCondition/IsEnglishLeaf.h"

const vector<string> ParseTree::sentenceLabels = {"SINV", "SBARQ", "SBAR", "SQ", "S"};

/**
 * Basic constructor for a ParseTree. Initializes the root node with the input.
 * @param root Root node of the tree
 */
ParseTree::ParseTree(ParseNode *root) {
    this->root = root;
}

/**
 * Another constructor of the ParseTree. The method takes the file containing a single line as input and constructs
 * the whole tree by calling the ParseNode constructor recursively.
 * @param file File containing a single line for a ParseTree
 */
ParseTree::ParseTree(istream &inputFile) {
    string line;
    getline(inputFile, line);
    if (line.find('(') != string::npos && line.find_last_of(')') != string::npos){
        line = Word::trim(line.substr(line.find('(') + 1, line.find_last_of(')') - line.find('(') - 1));
        root = new ParseNode(nullptr, line, false);
    } else {
        root = nullptr;
    }
}

ParseTree::ParseTree(const string& fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream::in);
    string line;
    getline(inputFile, line);
    if (line.find('(') != string::npos && line.find_last_of(')') != string::npos){
        line = Word::trim(line.substr(line.find('(') + 1, line.find_last_of(')') - line.find('(') - 1));
        root = new ParseNode(nullptr, line, false);
    } else {
        root = nullptr;
    }
    inputFile.close();
}

void ParseTree::setName(const string& _name) {
    this->name = _name;
}

string ParseTree::getName(){
    return name;
}

/**
 * Gets the next leaf node after the given leaf node in the ParseTree.
 * @param parseNode ParseNode for which next node is calculated.
 * @return Next leaf node after the given leaf node.
 */
ParseNode *ParseTree::nextLeafNode(ParseNode *parseNode) {
    NodeCollector nodeCollector = NodeCollector(root, new IsEnglishLeaf());
    vector<ParseNode*> leafList = nodeCollector.collect();
    for (int i = 0; i < leafList.size() - 1; i++){
        if (leafList.at(i) == parseNode){
            return leafList.at(i + 1);
        }
    }
    return nullptr;
}

/**
 * Gets the previous leaf node before the given leaf node in the ParseTree.
 * @param parseNode ParseNode for which previous node is calculated.
 * @return Previous leaf node before the given leaf node.
 */
ParseNode *ParseTree::previousLeafNode(ParseNode *parseNode) {
    NodeCollector nodeCollector = NodeCollector(root, new IsEnglishLeaf());
    vector<ParseNode*> leafList = nodeCollector.collect();
    for (int i = 1; i < leafList.size(); i++){
        if (leafList.at(i) == parseNode){
            return leafList.at(i - 1);
        }
    }
    return nullptr;
}

/**
 * Calls recursive method to calculate the number of all nodes, which have more than one children.
 * @return Number of all nodes, which have more than one children.
 */
int ParseTree::nodeCountWithMultipleChildren() {
    return root->nodeCountWithMultipleChildren();
}

/**
 * Calls recursive method to calculate the number of all nodes tree.
 * @return Number of all nodes in the tree.
 */
int ParseTree::nodeCount() {
    return root->nodeCount();
}

/**
 * Calls recursive method to calculate the number of all leaf nodes in the tree.
 * @return Number of all leaf nodes in the tree.
 */
int ParseTree::leafCount() {
    return root->leafCount();
}

bool ParseTree::isFullSentence() {
    if (root != nullptr && Symbol::contains(sentenceLabels, root->getData().getName())){
        return true;
    }
    return false;
}

/**
 * Saves the tree into the file with the given file name. The output file only contains one line representing tree.
 * @param fileName Output file name
 */
void ParseTree::save(const string& fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ostream::out);
    outputFile << "( ";
    outputFile << to_string();
    outputFile << " )\n";
    outputFile.close();
}

/**
 * Calls recursive function to convert the tree to a string.
 * @return A string which contains all words in the tree.
 */
string ParseTree::to_string() {
    return root->to_string();
}

/**
 * Calls recursive method to restore the parents of all nodes in the tree.
 */
void ParseTree::correctParents() {
    root->correctParents();
}

/**
 * Calls recursive method to remove all nodes starting with the symbol X. If the node is removed, its children are
 * connected to the next sibling of the deleted node.
 */
void ParseTree::removeXNodes() {
    root->removeXNodes();
}

/**
 * Calls recursive method to remove all punctuation nodes from the tree.
 */
void ParseTree::stripPunctuation() {
    root->stripPunctuation();
}

/**
 * Accessor method for the root node.
 * @return Root node
 */
ParseNode *ParseTree::getRoot() {
    return root;
}

/**
 * Calls recursive function to convert the tree to a sentence.
 * @return A sentence which contains all words in the tree.
 */
string ParseTree::toSentence() {
    return Word::trim(root->toSentence());
}

/**
 * Calls recursive function to count the number of words in the tree.
 * @param excludeStopWords If true, stop words are not counted.
 * @return Number of words in the tree.
 */
int ParseTree::wordCount(bool excludeStopWords) {
    return root->wordCount(excludeStopWords);
}

ParseTree::~ParseTree() {
    delete root;
}

/**
 * Generates a list of constituents in the parse tree and their spans.
 * @return A list of constituents in the parse tree and their spans.
 */
vector<ConstituentSpan> ParseTree::constituentSpanList() {
    vector<ConstituentSpan> result;
    if (root != nullptr){
        root->constituentSpanList(1, result);
    }
    return result;
}