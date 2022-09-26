#pragma once

#include "iterator.h"

class NullIterator : public Iterator
{
public:
    void first() override {}

    Shape* currentItem() const override {}

    void next() override {}

    bool isDone() const override {}
};