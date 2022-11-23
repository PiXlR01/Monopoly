//
// Created by Denis Vioreanu on 23.10.2022.
//

#ifndef MONOPOLY_PROPERTY_H
#define MONOPOLY_PROPERTY_H
#include "Box.h"

class Property : public Box
{
private:
    std::string color;
    int buyPrice;
    int mortgagePrice;
    int removeMortgagePrice;
    int rent;
    int rentWithAllColors;
    int rentWithOneHouse;
    int rentWithTwoHouses;
    int rentWithThreeHouses;
    int rentWithFourHouses;
    int pricePerHouse;
    int rentWithHotel;
    int pricePerHotel;
    int numberOfHouses;
    bool hasHotel;
    bool mortgaged;
    std::string owner;

public:
    Property(std::string name, std::string color, int buyPrice, int mortgagePrice, int removeMortgagePrice, int rent, int rentWithAllColors
            , int rentWithOneHouse, int rentWithTwoHouses, int rentWithThreeHouses, int rentWithFourHouses, int pricePerHouse, int rentWithHotel
            , int pricePerHotel) : Box(name, 'p'), color(color), buyPrice(buyPrice), mortgagePrice(mortgagePrice)
            , removeMortgagePrice(removeMortgagePrice), rent(rent), rentWithAllColors(rentWithAllColors), rentWithOneHouse(rentWithOneHouse)
            , rentWithTwoHouses(rentWithTwoHouses), rentWithThreeHouses(rentWithThreeHouses), rentWithFourHouses(rentWithFourHouses)
            , pricePerHouse(pricePerHouse), rentWithHotel(rentWithHotel), pricePerHotel(pricePerHotel), numberOfHouses(0), hasHotel(false), mortgaged(false) {}

    std::string getOwner()
    {
        return owner;
    }

    virtual std::string getColor() override
    {
        return color;
    }

    virtual void setOwner(std::string name) override
    {
        owner = name;
    }

    bool getHasHotel() const
    {
        return hasHotel;
    }

    bool isMortgaged() const override
    {
        return mortgaged;
    }

    void changeMortgageStatus(bool newStatus) override
    {
        this->mortgaged = newStatus;
    }

    virtual int getData(std::string data)
    {
        if (data == "buyPrice")
            return buyPrice;
        else if (data == "mortgagePrice")
            return mortgagePrice;
        else if (data == "rent")
            return rent;
        else if (data == "rentWithAllColors")
            return rentWithAllColors;
        else if (data == "pricePerHouse")
            return pricePerHouse;
        else if (data == "rentWithHotel")
            return rentWithHotel;
        else if (data == "numberOfHouses")
            return numberOfHouses;
        else if (data == "removeMortgagePrice")
            return removeMortgagePrice;
        else if (data == "rentWithOneHouse")
            return rentWithOneHouse;
        else if (data == "rentWithTwoHouses")
            return rentWithTwoHouses;
        else if (data == "rentWithThreeHouses")
            return rentWithThreeHouses;
        else if (data == "rentWithFourHouses")
            return rentWithFourHouses;
        else if (data == "pricePerHotel")
            return pricePerHotel;

        return 0;
    }

    void presentProperty()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Color: " << color << std::endl;
        std::cout << "Price: " << buyPrice << std::endl;
        std::cout << "Rent: " << rent << std::endl;
        std::cout << "Rent with group color: " << rentWithAllColors << std::endl;
        std::cout << "Rent with one house: " << rentWithOneHouse << std::endl;
        std::cout << "Rent with two house: " << rentWithTwoHouses << std::endl;
        std::cout << "Rent with three house: " << rentWithThreeHouses << std::endl;
        std::cout << "Rent with four house: " << rentWithFourHouses << std::endl;
        std::cout << "Rent with hotel: " << rentWithHotel << std::endl;
    }

    void increaseNumberOfHouses(int amount)
    {
        numberOfHouses += amount;
    }

    void setHasHotel(bool value)
    {
        hasHotel = value;
    }

    void resetProperty() override
    {
        numberOfHouses = 0;
        hasHotel = false;
        mortgaged = false;
    }
};


#endif //MONOPOLY_PROPERTY_H
