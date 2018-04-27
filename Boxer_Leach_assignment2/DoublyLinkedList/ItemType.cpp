//
// Created by Sandy Leach on 10/12/17.
//

#include "ItemType.h"
#include "cstdlib"
#include "iostream"

using namespace std;

ItemType::ItemType()
{
    this->value;
}

ItemType::RelationType ItemType::compareTo(ItemType &item)
{
    RelationType retval;

    if (this->value > item.value)
        retval = GREATER;
    else if (this->value == item.value)
        retval = EQUAL;
    else
        retval = LESS;

    return retval;
}

void ItemType::print()
{
    cout << this->value << " ";
}

void ItemType::initialize(int number)
{
    this->value = number;
}

int ItemType::getValue() const
{
    return this->value;
}
