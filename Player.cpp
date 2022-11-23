//
// Created by Denis Vioreanu on 23.10.2022.
//

#include "Player.h"
#include <cstdlib>

void Player::displayProperties()
{
    int i{ 1 };
    for (const auto p : properties)
    {
        std::cout << i << ". " << p->getName() << std::endl;
        i++;
    }
}

int Player::displayPropertiesWithoutMortgage()
{
    int i{ 1 };
    for (const auto p : properties)
    {
        if (!p->isMortgaged())
        {
            std::cout << i << ". " << p->getName() << std::endl;
            i++;
        }
    }
    return --i;
}

int Player::rollTheDices()
{
    int temp = this->positionCount;
    srand((unsigned) time(NULL));
    positionCount += (rand() % 12) + 1;
    if (positionCount > 39)
    {
        std::cout << "You passed through start, you got $200\n";
        positionCount -= 39;
        money += 200;
    }
    return this->positionCount - temp;
}

void Player::buyProperty(Box* box)
{
    this->properties.push_back(box);
    box->setOwner(this->name);
    this->money -= box->getData("buyPrice");
    std::cout << "TRANSACTION EFFECTUATED\n";
    std::cout << "You have left $" << this->money << std::endl;
}

bool Player::notEnoughMoney(double amountToPay)
{
    std::cout << "You need $" << amountToPay - this->money << " more in order to make your payment\n";
    std::cout << "To increase your money, try mortgaging one of your properties\n";

    int selection{ 0 };
    int position{ 0 };
    int numberOfProperties;

    while (this->money < amountToPay)
    {
        std::cout << "1. Mortgage a property\n";
        std::cout << "0. Give up\n";
        std::cout << "\nEnter your selection: ";
        std::cin >> selection;

        switch(selection)
        {
            case 1:
                numberOfProperties = displayPropertiesWithoutMortgage();
                if (numberOfProperties)
                {
                    do
                    {
                        std::cout << "Select a property: ";
                        std::cin >> position;
                    }while (position < 0 || position > numberOfProperties);

                    position--;
                    properties.at(position)->changeMortgageStatus(true);
                    this->hasMortgage = true;
                    money += properties.at(position)->getData("mortgagePrice");
                }
                else
                {
                    std::cout << "You don't have any properties\n";
                    outOfTheGame = true;
                    return false;
                }
                break;
            case 0:
                outOfTheGame = true;
                return false;
            default:
                std::cout << "Invalid operation";
        }
    }
    return true;
}

bool Player::rollTheDicesForPrison()
{
    srand((unsigned) time(NULL));
    int dice1, dice2;
    dice1 = (rand() % 6) + 1;
    dice2 = (rand() % 6) + 1;
    std::cout << "You got " << dice1 << " and " << dice2 << std::endl;
    return dice1 == dice2;
}

void Player::drawChanceCard(std::vector<Player> &player, std::vector<Box*> &box)
{
    bool owned = false;
    int random;
    int random2;
    int diceNumber;
    int amountToPay;
    srand((unsigned) time(NULL));
    random = rand() % 16;
    switch (random)
    {
        case 0:
            std::cout << "\nAdvance to B-dul Primaverii\n";
            positionCount = 39;
            redo = true;
            break;

        case 1:
            std::cout << "\nAdvance to Gara Progresu\n";
            if (positionCount > 5)
            {
                positionCount = 5;
                money += 200;
                std::cout << "Congratulations, you also passed through start and collected $200\n";
            }
            else
                positionCount = 5;
            redo = true;
            break;

        case 2:
            std::cout << "\nSpeed ticket, you have to pay $15\n";
            if (money >= 15)
            {
                money -= 15;
                std::cout << "You now have $" << money << " left\n";
            }
            else
            {
                if (notEnoughMoney(15))
                    money -= 15;
                else
                    outOfTheGame = true;
                std::cout << "You now have $" << money << " left\n";
            }
            break;

        case 3:
            std::cout << "\nGo back 3 places\n";
            positionCount -= 3;
            redo = true;
            break;

        case 4:
            std::cout << "\nAdvance to start, you get $200\n";
            positionCount = 0;
            money += 200;
            break;

        case 5:
            std::cout << "\nCongratulations, you got an escape from prison card\n";
            escapePrison++;
            break;

        case 6:
            std::cout << "\nYou've been chosen for council presidency, you have to pay each player $50\n";
            for (auto &p : player)
            {
                if (this->money >= 50)
                {
                    p.money += 50;
                    this->money -= 50;
                }
                else
                {
                    if (notEnoughMoney(50))
                    {
                        p.money += 50;
                        this->money -= 50;
                    }
                    else
                        outOfTheGame = true;
                }
            }
            break;

        case 7:
        case 11:
            std::cout << "\nAdvance to the nearest train station, if it is owned you need to\n";
            std::cout << "pay the owner double the rent, if it is not owned, you can buy it\n";
            owned = false;
            if (positionCount == 7)
            {
                positionCount = 15;
                std::cout << "You are now on Gara de est\n";
            }
            else if (positionCount == 22)
            {
                positionCount = 25;
                std::cout << "You are now on Gara Basarab\n";
            }
            else if (positionCount == 36)
            {
                positionCount = 5;
                std::cout << "You are now on Gara Progresu\n";
                std::cout << "You also passed through start so you get $200\n";
                money += 200;
            }
            for (auto &p : player)
            {
                if (box.at(positionCount)->getOwner() == p.getName())
                {
                    owned = true;
                    int count{ 0 };
                    for (const auto b : box)
                    {
                        if (b->getType() == 's')
                            if (b->getOwner() == p.getName())
                                count++;
                    }
                    int rent = 50 * count * 2;
                    std::cout << "This train station is owned by " << p.getName() << std::endl;
                    std::cout << "You need to pay him $" << rent << std::endl;
                    if (money >= rent)
                    {
                        money -= rent;
                        p.money += rent;
                    }
                    else
                    {
                        if (notEnoughMoney(rent))
                        {
                            money -= rent;
                            p.money += rent;
                        }
                        else
                            outOfTheGame = true;
                    }
                }
            }
            if (!owned)
                redo = true;
            break;

        case 8:
            std::cout << "\nAdvance to Titan\n";
            if (positionCount > 11)
            {
                positionCount = 11;
                std::cout << "Congratulations, you also passed through start and got $200\n";
            }
            else
                positionCount = 11;
            redo = true;
            break;

        case 9:
            std::cout << "\nAdvance to the nearest utility, if it is owned you need to\n";
            std::cout << "throw the dices and pay the owner 10 times the number on the\n";
            std::cout << "dices. If it is not owned you can buy it\n";
            if (positionCount == 7)
            {
                positionCount = 12;
                std::cout << "You are now on Uzina Electrica\n";
            }
            else if (positionCount == 22)
            {
                positionCount = 28;
                std::cout << "You are now on Uzina de Apa\n";
            }
            else if (positionCount == 36)
            {
                std::cout << "Congratulations, you also passed through start and got $200\n";
                money += 200;
                positionCount = 12;
                std::cout << "You are now on Uzina Electrica\n";
            }
            for (auto &p : player)
            {
                if (box.at(positionCount)->getOwner() == p.getName())
                {
                    owned = true;
                    diceNumber = rollTheDices();
                    std::cout << "This utility is owned by " << p.getName() << std::endl;
                    int rent = 10 * diceNumber;
                    std::cout << "You got " << diceNumber << " on the dices\n";
                    std::cout << "You need to pay him $" << rent << std::endl;
                    if (money >= rent)
                    {
                        money -= rent;
                        p.money += rent;
                    }
                    else
                    {
                        if (notEnoughMoney(rent))
                        {
                            money -= rent;
                            p.money += rent;
                        }
                        else
                            outOfTheGame = true;
                    }
                }
            }
            if (!owned)
                redo = true;
            break;

        case 10:
            std::cout << "\nAdvance to B-dul Eroilor\n";
            if (positionCount > 25)
            {
                std::cout << "Congratulations, you also passed through start and got $200\n";
                money += 200;
                positionCount = 24;
            }
            else
                positionCount = 24;
            redo = true;
            break;

        case 12:
            std::cout << "\nThe building loan has reached maturity, collect $150\n";
            money += 150;
            break;

        case 13:
            std::cout << "\nGo to prison\n";
            sendToPrison();
            break;

        case 14:
            std::cout << "\nGeneral fixes to all your properties\n";
            std::cout << "For each house - $25\n";
            std::cout << "For each hotel - $100\n";
            amountToPay = (25 * numberOfHouses) + (100 * numberOfHotels);
            if (money >= amountToPay)
            {
                money -= amountToPay;
                std::cout << "You now have $" << money << " left\n";
            }
            else
            {
                if (notEnoughMoney(amountToPay))
                    money -= amountToPay;
                else
                    outOfTheGame = true;
                std::cout << "You now have $" << money << " left\n";
            }
            break;

        case 15:
            std::cout << "\nMoney rain\n";
            std::cout << "Each player will be awarded a random amount of dollars between 300 and 600";
            srand((unsigned) time(NULL));
            for (auto &p : player)
            {
                random2 = rand()%(300 + 1) + 300;
                p.money += random2;
            }
            break;

        default:
            std::cout << "\n\n\nInvalid random number, check switch\n\n\n";
    }
}

void Player::drawCommunityChestCard(std::vector<Player> &player, std::vector<Box*> &box)
{
    int random;
    int amountToPay;
    srand((unsigned) time(NULL));
    random = rand() % 16;
    switch (random)
    {
        case 0:
            std::cout << "\nMedical bill, you have to pay $100\n";
            if (money >= 100)
                money -= 100;
            else
            {
                if (notEnoughMoney(100))
                    money -= 100;
                else
                    outOfTheGame = true;
            }
            std::cout << "You now have $" << money << " left\n";
            break;

        case 1:
            std::cout << "\nCollect $25 from consulting fees\n";
            money += 25;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 2:
            std::cout << "\nFrom selling stocks you get $50\n";
            money += 50;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 3:
            std::cout << "\nCongratulations, you got an escape from prison card\n";
            modifyEscapePrison(1);
            break;

        case 4:
            std::cout << "\nVacation fond has reached maturity, collect $100\n";
            money += 100;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 5:
            std::cout << "\nIt's your birthday, collect $10 from each player\n";
            for (auto &p : player)
            {
                if (p.getMoney() >= 10)
                {
                    p.modifyMoney(-10);
                    money += 10;
                }
                else
                {
                    if (p.notEnoughMoney(10))
                    {
                        money += 10;
                        p.modifyMoney(-10);
                    }
                    else
                        p.outOfTheGame = true;
                }
            }
            std::cout << "You now have $" << money << std::endl;
            break;

        case 6:
            std::cout << "\nIncome tax refund, collect $20\n";
            money += 20;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 7:
            std::cout << "\nTuition fee, you have to pay $50\n";
            if (money >= 50)
                money -= 50;
            else
            {
                if (notEnoughMoney(50))
                    money -= 50;
                else
                    outOfTheGame = true;
            }
            std::cout << "You now have $" << money << " left\n";
            break;

        case 8:
            std::cout << "\nYou inherited $100";
            money += 100;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 9:
            std::cout << "\nYou are evaluated for street repairs\n";
            std::cout << "Each house - $40\n";
            std::cout << "Each hotel - $115\n";
            amountToPay = (numberOfHouses * 40) + (numberOfHotels * 115);
            if (money >= amountToPay)
                money -= amountToPay;
            else
            {
                if (notEnoughMoney(amountToPay))
                    money -= amountToPay;
                else
                    outOfTheGame = true;
            }
            std::cout << "You now have $" << money << " left\n";
            break;

        case 10:
            std::cout << "\nYou've been sent to prison\n";
            sendToPrison();
            break;

        case 11:
            std::cout << "\nAdvance to start and collect $200\n";
            money += 200;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 12:
            std::cout << "\nYou got number 2 in a beauty contest, collect $10\n";
            money += 10;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 13:
            std::cout << "\nMedical fee, you have to pay $50\n";
            amountToPay = 50;
            if (money >= amountToPay)
                money -= amountToPay;
            else
            {
                if (notEnoughMoney(amountToPay))
                    money -= amountToPay;
                else
                    outOfTheGame = true;
            }
            std::cout << "You now have $" << money << " left\n";
            break;

        case 14:
            std::cout << "\nLife insurance has reached maturity, collect $100\n";
            money += 100;
            std::cout << "You now have $" << money << std::endl;
            break;

        case 15:
            std::cout << "\nBank error in your favor, collect $200\n";
            money += 200;
            std::cout << "You now have $" << money << std::endl;
            break;

        default:
            std::cout << "\n\n\nInvalid random number, check switch\n\n\n";
    }
}

void Player::freeProperties(std::vector<Box*> &box)
{
    for (auto p : properties)
    {
        for (auto b : box)
            if (p->getName() == b->getName())
                b->resetProperty();
    }
}

void Player::upForAuction(std::vector<Player> &players, std::vector<Box*> &box)
{
    int bidders;
    int currentBidPrice;
    int selection;
    std::string winner;
    std::cout << "\n\n===== Welcome to properties auction =====\n\n";
    for (auto &p : properties)
    {
        for (auto &b : box)
        {
            if (p->getName() == b->getName())
            {
                currentBidPrice = 10;
                std::cout << "Property name: " << p->getName() << std::endl;
                std::cout << "Starting bidding price: $10\n";
                do
                {
                    bidders = 0;
                    for (auto &player : players)
                    {
                        if (player.name == name)
                            continue;
                        std::cout << player.getName() << " is bidding...\n";
                        do
                        {
                            std::cout << "1. Enter an amount to bid\n";
                            std::cout << "0. Do not bid\n";
                            std::cin >> selection;
                        }while (selection != 1 && selection != 0);
                        if (selection == 1)
                        {
                            int amount;
                            std::cout << "Your bid amount needs to be higher than the last bid (" << currentBidPrice << "), and\n";
                            std::cout << "lower than your money (" << player.money << ")\n";
                            std::cout << "Enter bid amount: ";
                            std::cin >> amount;
                            if (amount > currentBidPrice && amount < player.money)
                            {
                                currentBidPrice = amount;
                                winner = player.name;
                                bidders++;
                            }
                            else
                                std::cout << "Incorrect amount. You do not bid this round\n";
                        }
                    }
                }while (bidders < 2);
                if (!winner.empty())
                {
                    for (auto &player : players)
                    {
                        if (player.name == winner)
                        {
                            std::cout << player.name << " won the bid\n";
                            player.properties.push_back(b);
                            player.money -= currentBidPrice;
                            std::cout << "You now own " << p->getName() << std::endl;
                            p->setOwner(player.name);
                        }
                    }
                }
                else
                {
                    std::cout << "No one wanted this property... it goes back to the bank\n";
                    p->setOwner("");
                }
                break;
            }
        }
    }
}

void Player::displayMortgagedProperties()
{
    int i{ 1 };
    char sel;
    std::string property;
    for (const auto &p : properties)
    {
        if (p->isMortgaged())
        {
            std::cout << i++ << ". " << p->getName() << " - " << p->getData("removeMortgagePrice");
        }
        std::cout << "Do you want to remove the mortgage from one of them?(Y/N): ";
        do
        {
            std::cin >> sel;
            if (sel != 'y' && sel != 'n' && sel != 'Y' && sel != 'N')
                std::cout << "Invalid selection, try again: ";
        }while(sel != 'y' && sel != 'n' && sel != 'Y' && sel != 'N');
        if (sel == 'Y' || sel == 'y')
        {
            do
            {
                bool ok = false;
                std::cout << "Choose one of the properties by name('none' to exit): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, property);
                if (property == "none")
                    return;
                for (auto &prop : properties)
                {
                    if (prop->getName() == property)
                    {
                        ok = true;
                        if (prop->isMortgaged())
                        {
                            if (this->money >= prop->getData("removeMortgagePrice"))
                            {
                                this->money -= prop->getData("removeMortgagePrice");
                                prop->changeMortgageStatus(false);
                            }
                            else
                                std::cout << "\nYou don't have enough money to remove the mortgage\n";
                        }
                        else
                            std::cout << "This property is not mortgaged";
                    }
                }
                if (!ok)
                    std::cout << "This property is not yours or you didn't type the name correctly\n";
            }while (true);
        }
        if (sel == 'n' || sel == 'N')
            return;
    }
}