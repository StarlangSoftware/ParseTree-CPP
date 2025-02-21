//
// Created by Olcay Taner YILDIZ on 2019-04-20.
//

#include <string>
#include "Symbol.h"
#include "StringUtils.h"

const vector<string> Symbol::nonTerminalList = {"ADJP", "ADVP", "CC", "CD", "CONJP", "DT", "EX", "FRAG", "FW", "IN", "INTJ", "JJ", "JJR", "JJS", "LS",
"LST", "MD", "NAC", "NN", "NNP", "NNPS", "NNS", "NP", "NX", "PDT", "POS", "PP", "PRN", "PRP", "PRP$", "PRT",
"PRT|ADVP", "QP", "RB", "RBR", "RP", "RRC", "S", "SBAR", "SBARQ", "SINV", "SQ", "SYM", "TO", "UCP", "UH", "VB", "VBD", "VBG", "VBN",
"VBP", "VBZ", "VP", "WDT", "WHADJP", "WHADVP", "WHNP", "WP", "WP$", "WRB", "X", "-NONE-"};
const vector<string> Symbol::phraseLabels = {"NP", "PP", "ADVP", "ADJP", "CC", "VG"};
const vector<string> Symbol::sentenceLabels = {"SINV","SBARQ","SBAR","SQ","S"};
const vector<string> Symbol::verbLabels = {"VB", "VBD", "VBG", "VBN","VBP", "VBZ", "VERB"};

/**
 * Constructor for Symbol class. Sets the name attribute.
 * @param name Name attribute
 */
Symbol::Symbol(const string& name) : Word(name) {
}

/**
 * Checks if this symbol is a verb type.
 * @return True if the symbol is a verb, false otherwise.
 */
bool Symbol::isVerb() const{
    return contains(verbLabels, name);
}

/**
 * Checks if the symbol is VP or not.
 * @return True if the symbol is VB, false otherwise.
 */
bool Symbol::isVP() const{
    return name == VPLabel;
}

/**
 * Checks if this symbol is a terminal symbol or not. A symbol is terminal if it is a punctuation symbol, or
 * if it starts with a lowercase symbol.
 * @return True if this symbol is a terminal symbol, false otherwise.
 */
bool Symbol::isTerminal() const{
    int i;
    if (name == "," || name == "." || name == "!" || name == "?" || name == ":"
        || name == ";" || name == "\"" || name == "''" || name == "'" || name == "`"
        || name == "``" || name == "..." || name == "-" || name == "--")
        return true;
    if (contains(nonTerminalList, name)){
        return false;
    }
    if (name == "I" || name == "A")
        return true;
    for (i = 0; i < name.size(); i++){
        if (name[i] >= 'a' && name[i] <= 'z'){
            return true;
        }
    }
    return false;
}

/**
 * Checks if this symbol can be a chunk label or not.
 * @return True if this symbol can be a chunk label, false otherwise.
 */
bool Symbol::isChunkLabel() const{
    if (Word::isPunctuation(name) || contains(sentenceLabels, StringUtils::replaceAll(name, "-.*","")) || contains(phraseLabels, StringUtils::replaceAll(name, "-.*", "")))
        return true;
    return false;
}

/**
 * Checks if a string is inside an array of strings.
 * @param list Array of string
 * @param searchedItem String to be searched.
 * @return True if the string is inside the array, false otherwise.
 */
bool Symbol::contains(const vector<string>& list, const string& searchedItem) {
    for (const string &item : list){
        if (item == searchedItem){
            return true;
        }
    }
    return false;
}

/**
 * If the symbol's data contains '-' or '=', this method trims all characters after those characters and returns
 * the resulting string.
 * @return Trimmed symbol.
 */
Symbol Symbol::trimSymbol() const{
    int minusIndex, equalIndex;
    if (StringUtils::startsWith(name, "-") || (name.find('-') == string::npos && name.find('=') == string::npos)){
        return *this;
    }
    minusIndex = name.find('-');
    equalIndex = name.find('=');
    if (minusIndex != string::npos || equalIndex != string::npos){
        if (minusIndex != string::npos && equalIndex != string::npos){
            if (minusIndex < equalIndex){
                return Symbol(name.substr(0, minusIndex));
            } else {
                return Symbol(name.substr(0, equalIndex));
            }
        } else {
            if (minusIndex != string::npos){
                return Symbol(name.substr(0, minusIndex));
            } else {
                return Symbol(name.substr(0, equalIndex));
            }
        }
    } else {
        return *this;
    }
}
