//
// Created by Denis Vioreanu on 26.10.2022.
//

#ifndef MONOPOLY_TRAIN_H
#define MONOPOLY_TRAIN_H
#include "Box.h"

class Train : public Box
{
private:
    std::string owner;
    int mortgagePrice;
    int removeMortgagePrice;
    bool mortgaged;

public:
    Train(std::string name, int mortgagePrice, int removeMortgagePrice)
        : Box(name, 's'), mortgagePrice(mortgagePrice), removeMortgagePrice(removeMortgagePrice), mortgaged(false) {}

    std::string getOwner() override
    {
        return owner;
    }

    void setOwner(std::string name) override
    {
        this->owner = name;
    }

    int getData(std::string data) override
    {
        if (data == "buyPrice")
            return 200;
        else if (data == "removeMortgagePrice")
            return removeMortgagePrice;
        else if (data == "mortgagePrice")
            return mortgagePrice;
    }

    void presentProperty()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Price: $200\n";
    }

    bool isMortgaged()
    {
        return mortgaged;
    }

    void resetProperty() override
    {
        owner = "";
        mortgaged = false;
    }

};


#endif //MONOPOLY_TRAIN_H
