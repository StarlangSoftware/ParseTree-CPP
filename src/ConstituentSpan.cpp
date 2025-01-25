//
// Created by Olcay Taner YILDIZ on 28.08.2020.
//

#include "ConstituentSpan.h"

/**
 * Constructor for the ConstituentSpan class. ConstituentSpan is a structure for storing constituents or phrases in
 * a sentence with a specific label. Sets the attributes.
 * @param _constituent Label of the span.
 * @param _start Start index of the span.
 * @param _end End index of the span.
 */
ConstituentSpan::ConstituentSpan(const Symbol& _constituent, int _start, int _end){
    this->constituent = _constituent;
    this->start = _start;
    this->end = _end;
}

/**
 * Accessor for the constituent attribute
 * @return Current constituent
 */
Symbol ConstituentSpan::getConstituent() const{
    return constituent;
}

/**
 * Accessor for the start attribute
 * @return Current start
 */
int ConstituentSpan::getStart() const {
    return start;
}

/**
 * Accessor for the end attribute
 * @return Current end
 */
int ConstituentSpan::getEnd() const {
    return end;
}
