//
// Created by Denis Vioreanu on 23.10.2022.
//

#ifndef MONOPOLY_BOX_H
#define MONOPOLY_BOX_H
#include <string>

class Box
{
protected:
    std::string name;
    char type; // p = property, s = train station, t = taxes, ? = chance/community chest, u = utility, g = go jail, f = free space
    bool mortgaged;
    std::string owner;

public:
    Box(std::string name, char type) : name(name), type(type), mortgaged(false), owner("") {}

    virtual std::string getName()
    {
        return name;
    }

    virtual void changeMortgageStatus(bool newStatus)
    {
        this->mortgaged = newStatus;
    }

    virtual bool isMortgaged() const
    {
        return mortgaged;
    }

    virtual void resetProperty()
    {
        mortgaged = false;
        owner = "";
    }

    char getType()
    {
        return type;
    }
    virtual std::string getOwner()
    {
        return owner;
    }

    virtual int getData(std::string data)
    {
        if (data == "removeMortgagePrice")
            return 110;
        else if (data == "mortgagePrice")
            return 100;
        else if (data == "buyPrice")
            return 150;
    }
    virtual void setOwner(std::string name)
    {
        this->owner = name;
    }
    virtual std::string getColor() {};
};


#endif //MONOPOLY_BOX_H
