//
// Created by Olcay Taner YILDIZ on 28.08.2020.
//

#ifndef PARSETREE_CONSTITUENTSPAN_H
#define PARSETREE_CONSTITUENTSPAN_H


#include "Symbol.h"

class ConstituentSpan {
private:
    Symbol constituent = Symbol("");
    int start;
    int end;
public:
    ConstituentSpan(const Symbol& _constituent, int _start, int _end);
    Symbol getConstituent();
    int getStart() const;
    int getEnd() const;
};


#endif //PARSETREE_CONSTITUENTSPAN_H
