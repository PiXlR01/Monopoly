//
// Created by Denis Vioreanu on 23.10.2022.
//

#ifndef MONOPOLY_TAXES_H
#define MONOPOLY_TAXES_H
#include "Box.h"

class Taxes : public Box
{
private:
    char taxType; // l = luxury tax, i = income tax

public:
    Taxes(std::string name, char taxType) : Box(name, 't'), taxType(taxType) {}

    char getTaxType()
    {
        return taxType;
    }
};


#endif //MONOPOLY_TAXES_H
