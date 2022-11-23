//
// Created by Denis Vioreanu on 23.10.2022.
//

#ifndef MONOPOLY_PLAYER_H
#define MONOPOLY_PLAYER_H
#include <string>
#include <vector>
#include "Box.h"

class Player
{
private:
    std::string name;
    double money;
    int positionCount; // min 0 max 39
    std::vector<Box*> properties;
    int numberOfHouses;
    int numberOfHotels;
    int escapePrison;
    bool inPrison;
    bool hasMortgage;
    bool redo;
    int prisonEscapeTries;
    bool outOfTheGame;

public:
    Player(std::string name) : name(name), money(1500), positionCount(0),numberOfHouses(0), numberOfHotels(0), hasMortgage(false), escapePrison(0), inPrison(false), redo(false), prisonEscapeTries(0), outOfTheGame (false) {}

    std::string getName() const
    {
        return name;
    }

    void setName(std::string newName)
    {
        this->name = newName;
    }

    bool hasMortgagedProperty()
    {
        return hasMortgage;
    }

    double getMoney() const
    {
        return money;
    }

    int getNumberOfHouses() const
    {
        return numberOfHouses;
    }

    int getNumberOfHotels() const
    {
        return numberOfHotels;
    }

    int getPositionCount() const
    {
        return positionCount;
    }

    void modifyMoney(double money_v)
    {
        this->money += money_v;
    }

    void setRedo(bool value)
    {
        redo = value;
    }

    bool getRedo()
    {
        return redo;
    }

    void increaseNumberOfHouses(int nr)
    {
        this->numberOfHouses += nr;
    }

    void increaseNumberOfHotels(int nr)
    {
        this->numberOfHotels += nr;
    }

    int getEscapePrison()
    {
        return escapePrison;
    }

    void escapeFromPrison()
    {
        inPrison = false;
    }

    void modifyEscapePrison(int amount)
    {
        escapePrison += amount;
    }

    void sendToPrison()
    {
        positionCount = 10;
        inPrison = true;
    }
    bool isInPrison()
    {
        return inPrison;
    }

    int getPrisonEscapeTries()
    {
        return prisonEscapeTries;
    }

    void increasePrisonEscapeTries()
    {
        prisonEscapeTries++;
    }

    void setPrisonEscapeTries(int amount)
    {
        prisonEscapeTries = amount;
    }

    bool isOut()
    {
        return outOfTheGame;
    }

    int displayPropertiesWithoutMortgage();
    void displayProperties();
    bool notEnoughMoney(double amountToPay);
    int rollTheDices();
    bool rollTheDicesForPrison();
    void buyProperty(Box* box);
    void drawCommunityChestCard(std::vector<Player> &player, std::vector<Box*> &box);
    void drawChanceCard(std::vector<Player> &player, std::vector<Box*> &box);
    void freeProperties(std::vector<Box*> &box);
    void upForAuction(std::vector<Player> &players, std::vector<Box*> &box);
    void displayMortgagedProperties();
};


#endif //MONOPOLY_PLAYER_H
