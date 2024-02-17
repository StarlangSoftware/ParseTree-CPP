//
// Created by Olcay Taner YILDIZ on 2019-04-20.
//

#ifndef PARSETREE_SYMBOL_H
#define PARSETREE_SYMBOL_H

#include <vector>
#include "Dictionary/Word.h"

class Symbol : public Word{
private:
    static const vector<string> nonTerminalList;
    static const vector<string> phraseLabels;
    static const vector<string> sentenceLabels;
    static const vector<string> verbLabels;
    string VPLabel = "VP";
public:
    Symbol() = default;
    explicit Symbol(const string& name);
    bool isVerb() const;
    bool isVP() const;
    bool isTerminal() const;
    bool isChunkLabel() const;
    Symbol trimSymbol() const;
    static bool contains(const vector<string>& list, const string& searchedItem);
    bool operator==(const Symbol &anotherSymbol) const{
        return (name == anotherSymbol.name);
    }
    bool operator<(const Symbol &anotherSymbol) const{
        return (name < anotherSymbol.name);
    }
    bool operator>(const Symbol &anotherSymbol) const{
        return (name > anotherSymbol.name);
    }
};


#endif //PARSETREE_SYMBOL_H
