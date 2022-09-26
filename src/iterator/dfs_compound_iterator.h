#pragma once

#include "iterator.h"
#include "../shape.h"

class CompoundShape;

template<class ForwardIterator>
class DFSCompoundIterator : public Iterator
{
public:
    DFSCompoundIterator(ForwardIterator begin, ForwardIterator end) {}

    void first() override {}

    Shape* currentItem() const override {}

    void next() override {}

    bool isDone() const override {}
};