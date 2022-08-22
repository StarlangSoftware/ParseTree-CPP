//
// Created by Olcay Taner YILDIZ on 28.08.2020.
//

#include "ConstituentSpan.h"

ConstituentSpan::ConstituentSpan(Symbol constituent, int start, int end){
    this->constituent = constituent;
    this->start = start;
    this->end = end;
}

Symbol ConstituentSpan::getConstituent() {
    return constituent;
}

int ConstituentSpan::getStart() {
    return start;
}

int ConstituentSpan::getEnd() {
    return end;
}
