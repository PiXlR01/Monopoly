//
// Created by Denis Vioreanu on 23.10.2022.
//

#ifndef MONOPOLY_CARDS_H
#define MONOPOLY_CARDS_H
#include "Box.h"

class Cards : public Box
{
private:
    char cardType; // c = community chest, ? = chance

public:
    Cards(std::string name, char cardType) : Box(name, '?'), cardType(cardType) {}

    char getCardType()
    {
        return cardType;
    }
};


#endif //MONOPOLY_CARDS_H
