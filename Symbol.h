//
// Created by Olcay Taner YILDIZ on 2019-04-20.
//

#ifndef PARSETREE_SYMBOL_H
#define PARSETREE_SYMBOL_H

#include <vector>
#include "Word.h"

class Symbol : public Word{
private:
    vector<string> nonTerminalList = {"ADJP", "ADVP", "CC", "CD", "CONJP", "DT", "EX", "FRAG", "FW", "IN", "INTJ", "JJ", "JJR", "JJS", "LS",
                                      "LST", "MD", "NAC", "NN", "NNP", "NNPS", "NNS", "NP", "NX", "PDT", "POS", "PP", "PRN", "PRP", "PRP$", "PRT",
                                      "PRT|ADVP", "QP", "RB", "RBR", "RP", "RRC", "S", "SBAR", "SBARQ", "SINV", "SQ", "SYM", "TO", "UCP", "UH", "VB", "VBD", "VBG", "VBN",
                                      "VBP", "VBZ", "VP", "WDT", "WHADJP", "WHADVP", "WHNP", "WP", "WP$", "WRB", "X", "-NONE-"};
    vector<string> phraseLabels = {"NP", "PP", "ADVP", "ADJP", "CC", "VG"};
    vector<string> sentenceLabels = {"SINV","SBARQ","SBAR","SQ","S"};
    vector<string> verbLabels = {"VB", "VBD", "VBG", "VBN","VBP", "VBZ", "VERB"};
    string VPLabel = "VP";
public:
    explicit Symbol(string name);
    bool isVerb();
    bool isVP();
    bool isTerminal();
    bool isChunkLabel();
    Symbol trimSymbol();
    static bool contains(vector<string> list, string searchedItem);
    bool operator==(const Symbol &anotherSymbol) const{
        return (name == anotherSymbol.name);
    }
    bool operator<(const Symbol &anotherSymbol) const{
        return (name < anotherSymbol.name);
    }
};


#endif //PARSETREE_SYMBOL_H
