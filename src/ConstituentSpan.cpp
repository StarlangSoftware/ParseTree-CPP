//
// Created by Olcay Taner YILDIZ on 28.08.2020.
//

#include "ConstituentSpan.h"

ConstituentSpan::ConstituentSpan(const Symbol& _constituent, int _start, int _end){
    this->constituent = _constituent;
    this->start = _start;
    this->end = _end;
}

Symbol ConstituentSpan::getConstituent() const{
    return constituent;
}

int ConstituentSpan::getStart() const {
    return start;
}

int ConstituentSpan::getEnd() const {
    return end;
}
