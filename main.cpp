#include <iostream>
#include "Player.h"
#include "Property.h"
#include "Cards.h"
#include "Taxes.h"
#include "Train.h"
#include "Player.cpp"

void displayRules();
void displayPlayers(const std::vector<Player> &players);
void populateTable(std::vector<Box*> &table);
void play(std::vector<Box*> &table, std::vector<Player> &players);
int checkForMultipleTrainStations(std::vector<Box*> &box, const Player &player);
int checkForMultipleUtilities(std::vector<Box*> &box, const Player &player);
void deletePlayer(std::string name, std::vector<Player> &player, std::vector<Box*> &box);
bool payAmount(Player &player, double amount, std::vector<Box*> &box, std::vector<Player> &players);
int remainingPlayers(std::vector<Player> &players);

int main()
{
    std::vector<Box*> table;
    for (size_t i = 0; i <= 39; i++)
    {
        Box* ptr = nullptr;
        table.push_back(ptr);
    }
    populateTable(table);
    std::vector<Player> players;

    std::cout << "\nWelcome to Monopoly\n\n";
    int playersNumber;
    do
    {
        std::cout << "Enter the number of players(between 2 and 8): ";
        std::cin >> playersNumber;
        if (playersNumber < 2)
            std::cout << "\nYou need at least 2 players in order to play the game\n";
        if (playersNumber > 8)
            std::cout << "\nYou cannot be more than 8 players in order to play the game\n";
    }while (playersNumber < 2 || playersNumber > 8);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 1; i <= playersNumber; i++)
    {
        do
        {
            std::cout << "Enter player number " << i << " name: ";
            std::string Name;
            std::getline(std::cin, Name);
            if(Name.empty())
                std::cout << "\nPlayer name cannot be empty!\n";
            else
            {
                players.emplace_back(Player(Name));
                break;
            }
        }while(true);
    }

    int selection;
    int ok{ 1 };
    do
    {
        std::cout << "1. Start\n";
        std::cout << "2. Display players\n";
        std::cout << "3. Display rules\n\n";
        std::cout << "0. Quit game\n";
        std::cout << "\nEnter your selection: ";
        std::cin >> selection;

        switch(selection)
        {
            case 1:
                play(table, players);
                ok = 0;
                break;
            case 2:
                displayPlayers(players);
                break;
            case 3:
                displayRules();
                break;
            case 0:
                ok = 0;
                break;
            default:
                std::cout << "\nInvalid selection, please try again\n\n";
        }
    }while(ok);

    return 0;
}

void displayPlayers(const std::vector<Player> &players)
{
std::cout << "========== Players List ==========\n";
for (auto const &player : players)
std::cout << player.getName() << std::endl;
std::cout << "==================================\n";
}

void populateTable(std::vector<Box*> &table)
{
    table.at(0) = new Box("Start", 'f');
    table.at(1) = new Property("Rahova", "Brown", 60, 30, 33, 2, 4, 10, 30, 90, 160, 50, 250, 50);
    table.at(2) = new Cards("Cufarul comunitatii", 'c');
    table.at(3) = new Property("Giulesti", "Brown", 60, 30, 33, 4, 8, 20, 60, 180, 320, 50, 450, 50);
    table.at(4) = new Taxes("Impozit pe venit", 'i');
    table.at(5) = new Train("Gara Progresu", 100, 110);
    table.at(6) = new Property("Balta alba", "LightBlue", 100, 50, 55, 6, 12, 30, 90, 270, 400, 50, 550, 50);
    table.at(7) = new Cards("Sansa", '?');
    table.at(8) = new Property("Pantelimon", "LightBlue", 100, 50, 55, 6, 12, 30, 90, 270, 400, 50, 550, 50);
    table.at(9) = new Property("Berceni", "LightBlue", 120, 60, 66, 8, 16, 40, 100, 300, 450, 50, 600, 50);
    table.at(10) = new Box("Jail", 'f');
    table.at(11) = new Property("Titan", "Purple", 140, 70, 77, 10, 20, 50, 150, 450, 625, 100, 750, 100);
    table.at(12) = new Box("Uzina electrica", 'u');
    table.at(13) = new Property("Colentina", "Purple", 140, 70, 77, 10, 20, 50, 150, 450, 625, 100, 750, 100);
    table.at(14) = new Property("Tei", "Purple", 160, 80, 88, 12, 24, 60, 180, 500, 700, 100, 900, 100);
    table.at(15) = new Train("Gara de est", 100, 110);
    table.at(16) = new Property("Bulevardul Timisoara", "Orange", 180, 90, 99, 14, 28, 70, 200, 550, 750, 100, 950, 100);
    table.at(17) = new Cards("Cufarul comunitatii", 'c');
    table.at(18) = new Property("Bulevardul Brasov", "Orange", 180, 90, 99, 14, 28, 70, 200, 550, 750, 100, 950, 100);
    table.at(19) = new Property("Drumul Taberei", "Orange", 200, 100, 110, 16, 32, 80, 220, 600, 800, 100, 1000, 100);
    table.at(20) = new Box("Parcare gratuita", 'f');
    table.at(21) = new Property("Bulevardul Carol", "Red", 220, 110, 121, 18, 36, 90, 250, 700, 875, 150, 1050, 150);
    table.at(22) = new Cards("Sansa", '?');
    table.at(23) = new Property("Bulevardul Kogalniceanu", "Red", 220, 110, 121, 18, 36, 90, 250, 700, 875, 150, 1050, 150);
    table.at(24) = new Property("Bulevardul Eroilor", "Red", 240, 120, 132, 20, 40, 100, 300, 750, 925, 150, 1100, 150);
    table.at(25) = new Train("Gara Basarab", 100, 110);
    table.at(26) = new Property("Bulevardul Titulescu", "Yellow", 260, 130, 143, 22, 44, 110, 330, 800, 975, 150, 1150, 150);
    table.at(27) = new Property("Bulevardul 1 Mai", "Yellow", 260, 130, 143, 22, 44, 110, 330, 800, 975, 150, 1150, 150);
    table.at(28) = new Box("Uzina de apa", 'u');
    table.at(29) = new Property("Calea Dorobantilor", "Yellow", 280, 140, 154, 24, 48, 120, 360, 850, 1025, 150, 1200, 150);
    table.at(30) = new Box("Go to jail", 'g');
    table.at(31) = new Property("Piata unirii", "Green", 300, 150, 165, 26, 52, 130, 390, 900, 1100, 200, 1275, 200);
    table.at(32) = new Property("Cotroceni", "Green", 300, 150, 165, 26, 52, 130, 390, 900, 1100, 200, 1275, 200);
    table.at(33) = new Cards("Cufarul Comunitatii", 'c');
    table.at(34) = new Property("Calea Victoriei", "Green", 320, 160, 176, 28, 56, 150, 450, 1000, 1200, 200, 1400, 200);
    table.at(35) = new Train("Gara de nord", 100, 110);
    table.at(36) = new Cards("Sansa", '?');
    table.at(37) = new Property("Bulevardul Magheru", "DarkBlue", 350, 175, 193, 35, 70, 175, 500, 1100, 1300, 200, 1500, 200);
    table.at(38) = new Taxes("Taxa de lux", 'l');
    table.at(39) = new Property("Bulevardul Primaverii", "DarkBlue", 400, 200, 220, 50, 100, 200, 600, 1400, 1700, 200, 2000, 200);
}

void play(std::vector<Box*> &table, std::vector<Player> &players)
{
    do
    {
        for (auto &player : players)
        {
            if (remainingPlayers(players) == 1)
                break;
            if (!player.getName().empty())
            {
                std::cout << "\n\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << player.getName() << "'s turn\n";
                std::cout << "Money: $" << player.getMoney() << std::endl;
                std::cout << "Properties:\n";
                player.displayProperties();
                std::cout << "You are currently at " << table.at(player.getPositionCount())->getName() << std::endl;
                if (player.hasMortgagedProperty())
                {
                    std::cout << "You have the following mortgaged properties:\n";
                    player.displayMortgagedProperties();
                }
                if (player.isInPrison())
                {
                    std::cout << "You are currently in prison\n";
                    std::cout << "In order to escape you need to have an escape card, to get a double when you roll the dices, or to pay $50\n";
                    if (player.getEscapePrison()) // returns the number of escape cards
                    {
                        std::cout << "Congratulations, you escaped with an escape card, you are free to go\n";
                        player.modifyEscapePrison(-1);
                        player.escapeFromPrison();
                    }
                    else
                    {
                        if (player.getPrisonEscapeTries() == 3)
                        {
                            std::cout << "You ran out of tries, you need to pay the $50 fee\n";
                            if (!payAmount(player, 50, table, players))
                                continue;
                            player.setPrisonEscapeTries(0);
                            player.escapeFromPrison();
                        }
                        else
                        {
                            std::cout << "1. Throw the dices.\n*Be careful, if you don't get a double, you wont do anything your turn\n"
                                         "and you have to wait for the next time*\n";
                            std::cout << "2. Pay $50 and get out right away\n";
                            int decision;
                            do
                            {
                                std::cin >> decision;
                                if (decision != 1 && decision != 2)
                                    std::cout << "\nInvalid selection\n";
                            }while (decision != 1 && decision != 2);

                            if (decision == 1)
                            {
                                if (player.rollTheDicesForPrison()) // returns true if both dices are equal
                                {
                                    std::cout << "Congratulations, you escaped\n";
                                    player.escapeFromPrison();
                                    player.setPrisonEscapeTries(0);
                                }
                                else
                                {
                                    player.increasePrisonEscapeTries();
                                    std::cout << "Try again next time\n";
                                    continue;
                                }
                            }
                            else if (decision == 2)
                            {
                                if (!payAmount(player, 50, table, players))
                                    continue;
                                player.setPrisonEscapeTries(0);
                                player.escapeFromPrison();
                            }
                        }
                    }
                }
                std::cout << "Press enter to roll the dices\n";
                std::cin.get();
                int dicesNumber = player.rollTheDices();
                do
                {
                    if (player.isOut())
                    {
                        deletePlayer(player.getName(), players, table);
                        continue;
                    }
                    player.setRedo(false);
                    if (table.at(player.getPositionCount())->getType() == 'p')
                    {
                        Property* property = dynamic_cast<Property*>(table.at(player.getPositionCount()));
                        std::cout << "You landed on " << property->getName() << std::endl;
                        if (!property->getOwner().empty()) //false if property is owned, true otherwise, reversed with "!"
                        {
                            if (property->getOwner() != player.getName())
                            {
                                for (auto &p : players)
                                    if (p.getName() == property->getOwner())
                                    {
                                        if (!property->isMortgaged())
                                        {
                                            int numberOfHouses = property->getData("numberOfHouses");
                                            if (numberOfHouses)
                                            {
                                                int rent{ 0 };
                                                switch(numberOfHouses)
                                                {
                                                    case 1:
                                                        rent = property->getData("rentWithOneHouse");
                                                        std::cout << "You need to pay " << p.getName() << " $" << rent;
                                                        break;
                                                    case 2:
                                                        rent = property->getData("rentWithTwoHouses");
                                                        std::cout << "You need to pay " << p.getName() << " $" << rent;
                                                        break;
                                                    case 3:
                                                        rent = property->getData("rentWithThreeHouses");
                                                        std::cout << "You need to pay " << p.getName() << " $" << rent;
                                                        break;
                                                    case 4:
                                                        rent = property->getData("rentWithFourHouses");
                                                        std::cout << "You need to pay " << p.getName() << " $" << rent;
                                                        break;
                                                    default:
                                                        std::cout << "\n\n\nERROR: NUMBER OF HOUSES WAS NOT IN RANGE!\n\n\n";
                                                }
                                                if (property->getHasHotel())
                                                    rent = property->getData("rentWithHotel");
                                                if (!payAmount(player, rent, table, players))
                                                    continue;
                                                else
                                                    p.modifyMoney(rent);
                                            }
                                            else if (!property->getHasHotel())
                                            {
                                                int rent = property->getData("rent");
                                                std::cout << "You need to pay " << p.getName() << " $" << rent << std::endl;
                                                if (!payAmount(player, rent, table, players))
                                                    continue;
                                                else
                                                    p.modifyMoney(rent);
                                            }
                                            else
                                            {
                                                int rent = property->getData("rentWithHotel");
                                                std::cout << "You need to pay " << p.getName() << " $" << rent << std::endl;
                                                if (!payAmount(player, rent, table, players))
                                                    continue;
                                                else
                                                    p.modifyMoney(rent);
                                            }
                                        }
                                        else
                                            std::cout << "This property is owned but is mortgaged for now, nothing happens\n";
                                    }
                            }
                            else
                            {
                                bool ok = true;
                                for (const auto t : table)
                                {
                                    if (t->getType() == 'p')
                                    {
                                        if (t->getColor() == property->getColor())
                                            if (t->getOwner() != player.getName())
                                                ok = false;
                                    }
                                }
                                std::cout << "This is your property\n";
                                if (ok)
                                {
                                    if (property->getData("numberOfHouses") < 4)
                                    {
                                        char sel;
                                        do
                                        {
                                            std::cout << "You have all the properties from this color\n";
                                            std::cout << "You currently have " << property->getData("numberOfHouses") << " houses built\n";
                                            std::cout << "Do you want to build houses on it?(Y/N): ";
                                            std::cin >> sel;
                                        }while (sel != 'y' && sel != 'Y' && sel != 'n' && sel != 'N');
                                        if (sel == 'y' || sel == 'Y')
                                        {
                                            int number;
                                            do
                                            {
                                                std::cout << "A house costs $" << property->getData("pricePerHouse");
                                                std::cout << "You can build " << 4 - property->getData("numberOfHouses") << " more houses\n";
                                                std::cout << "How many do you want to build: ";
                                                std::cin >> number;
                                            }while (number < 0 || number > 4 - property->getData("numberOfHouses"));
                                            if (property->getData("pricePerHouse") * number <= player.getMoney())
                                            {
                                                property->increaseNumberOfHouses(number);
                                                player.increaseNumberOfHouses(number);
                                            }
                                            else
                                                std::cout << "Sorry, you don't have enough money\n";
                                        }
                                    }
                                    if (property->getData("numberOfHouses") == 4)
                                    {
                                        char sel;
                                        do
                                        {
                                            std::cout << "You have 4 houses on this property\n";
                                            std::cout << "Do you want to build a hotel?(Y/N): ";
                                            std::cin >> sel;
                                        }while (sel != 'y' && sel != 'Y' && sel != 'n' && sel != 'N');
                                        if (sel == 'y' || sel == 'Y')
                                        {
                                            if (player.getMoney() >= property->getData("pricePerHotel"))
                                            {
                                                property->setHasHotel(true);
                                                player.increaseNumberOfHotels(1);
                                                property->increaseNumberOfHouses(-4);
                                                std::cout << "Your property now has a hotel on it\n";
                                            }
                                            else
                                                std::cout << "Sorry, you don't have enough money\n";
                                        }
                                    }
                                }
                                else
                                    std::cout << "You need to buy all the properties from this color group in order to build houses\n";
                            }
                        }
                        else
                        {
                            int selection;
                            std::cout << "This property is not owned by anyone\n";
                            property->presentProperty();
                            do
                            {
                                std::cout << "1. Buy property\n";
                                std::cout << "2. Continue\n";
                                std::cout << "\nEnter selection: ";
                                std::cin >> selection;
                            }while (selection != 1 && selection != 2);

                            if (selection == 1)
                            {
                                if (player.getMoney() >= property->getData("buyPrice"))
                                {
                                    player.buyProperty(property);
                                    std::cout << "You now own " << property->getName() << std::endl;
                                }
                                else
                                    std::cout << "Sorry, you don't have enough money\n";
                            }

                        }
                    }
                    else if (table.at(player.getPositionCount())->getType() == 's')
                    {
                        Train* train = dynamic_cast<Train*>(table.at(player.getPositionCount()));
                        std::cout << "You landed on " << train->getName() << std::endl;
                        if (train->getOwner().empty())
                        {
                            int selection;
                            std::cout << "This train station is not owned by anyone\n";
                            train->presentProperty();
                            do
                            {
                                std::cout << "1. Buy property\n";
                                std::cout << "2. Continue\n";
                                std::cout << "\nEnter selection: ";
                                std::cin >> selection;
                            }while (selection != 1 && selection != 2);

                            if (selection == 1)
                            {
                                if (player.getMoney() >= 200)
                                {
                                    player.buyProperty(train);
                                    std::cout << "You now own " << train->getName() << std::endl;
                                }
                                else
                                    std::cout << "Sorry, you don't have enough money\n";
                            }
                        }
                        else
                        {
                            for (auto &p : players)
                            {
                                if (p.getName() == train->getOwner())
                                {
                                    if (p.getName() == player.getName())
                                        std::cout << "This is your train station, nothing happens\n";
                                    else
                                    {
                                        if (train->isMortgaged())
                                        {
                                            std::cout << "This train station is owned buy it is mortgaged for now, nothing happens\n";
                                        }
                                        else
                                        {
                                            int rent = 25 * checkForMultipleTrainStations(table, p);
                                            std::cout << "This train station is owned by " << p.getName() << std::endl;
                                            std::cout << "He owns " << checkForMultipleTrainStations(table, p) << " train stations\n";
                                            std::cout << "Therefore you have to pay him $" << rent << std::endl;
                                            if (!payAmount(player, rent, table, players))
                                                continue;
                                            else
                                                p.modifyMoney(rent);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (table.at(player.getPositionCount())->getType() == 't')
                    {
                        Taxes* tax = dynamic_cast<Taxes*>(table.at(player.getPositionCount()));
                        if (tax->getTaxType() == 'l')
                        {
                            std::cout << "You landed on luxury tax\n";
                            std::cout << "You need to pay $100\n";
                            if (!payAmount(player, 100, table, players))
                                continue;
                        }
                        if (tax->getTaxType() == 'i')
                        {
                            std::cout << "You landed on income tax\n";
                            std::cout << "You need to pay $200\n";
                            if (!payAmount(player, 200, table, players))
                                continue;
                        }
                    }
                    else if (table.at(player.getPositionCount())->getType() == 'u')
                    {
                        Box* utility = table.at(player.getPositionCount());
                        std::cout << "You landed on " << utility->getName() << std::endl;
                        if (table.at(player.getPositionCount())->getType() == 'u')
                        {
                            if (utility->getOwner() == player.getName())
                            {
                                std::cout << "This is your property, nothing happens\n";
                            }
                            else if (utility->getOwner().empty())
                            {
                                std::cout << "This property is not owned by anyone\n";
                                int selection;
                                std::cout << "Name: " << utility->getName() << std::endl;
                                std::cout << "Price: $150\n";
                                do
                                {
                                    std::cout << "1. Buy property\n";
                                    std::cout << "2. Continue\n";
                                    std::cout << "\nEnter selection: ";
                                    std::cin >> selection;
                                }while (selection != 1 && selection != 2);
                                if (selection == 1)
                                {
                                    if (player.getMoney() >= 150)
                                    {
                                        player.buyProperty(utility);
                                        std::cout << "You now own " << utility->getName() << std::endl;
                                    }
                                    else
                                        std::cout << "Sorry, you don't have enough money\n";
                                }
                            }
                            else
                            {
                                for (auto &p : players)
                                {
                                    if (p.getName() == utility->getOwner())
                                    {
                                        int numberOfUtilities = checkForMultipleUtilities(table, p);
                                        std::cout << "This property is owned by " << p.getName() << std::endl;
                                        std::cout << "He owns " << numberOfUtilities << " utilities";
                                        if (numberOfUtilities == 1)
                                        {
                                            int rent = dicesNumber * 4;
                                            std::cout << "\nYou need to pay him 4 times the numbers on the dices\n";
                                            std::cout << "The amount you need to pay him is $" << rent << std::endl;
                                            if (!payAmount(player, rent, table, players))
                                                continue;
                                            else
                                                p.modifyMoney(rent);
                                        }
                                        else if (numberOfUtilities == 2)
                                        {
                                            int rent = dicesNumber * 10;
                                            std::cout << "\nYou need to pay him 10 times the numbers on the dices\n";
                                            std::cout << "The amount you need to pay him is $" << rent << std::endl;
                                            if (!payAmount(player, rent, table, players))
                                                continue;
                                            else
                                                p.modifyMoney(rent);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (table.at(player.getPositionCount())->getType() == 'g')
                    {
                        std::cout << "You landed on 'Go to jail' section\n";
                        std::cout << "Unfortunately, you have to go to the jail without passing through start and getting $200\n";
                        player.sendToPrison();
                    }
                    else if (table.at(player.getPositionCount())->getType() == 'f')
                    {
                        std::cout << "You landed on " << table.at(player.getPositionCount())->getName() << std::endl;
                        std::cout << "Nothing happens, press enter to continue...\n";
                    }
                    else if (table.at(player.getPositionCount())->getType() == '?')
                    {
                        Cards* card = dynamic_cast<Cards*>(table.at(player.getPositionCount()));
                        if (card->getCardType() == 'c')
                        {
                            std::cout << "You landed on community chest\n";
                            player.drawCommunityChestCard(players, table);
                        }
                        else
                        {
                            std::cout << "You landed on chance\n";
                            player.drawChanceCard(players, table);
                        }
                    }
                }while(player.getRedo());
            }
        }
    }while (remainingPlayers(players) != 1);

    for (const auto &p : players)
    {
        if (!p.getName().empty())
        {
            std::cout << "The winner is - " << p.getName() << std::endl;
            break;
        }
    }
}

int checkForMultipleTrainStations(std::vector<Box*> &box, const Player &player)
{
    int count{ 0 };
    for (const auto b : box)
    {
        if (b->getType() == 's')
            if (b->getOwner() == player.getName())
                count++;
    }
    return count;
}

int checkForMultipleUtilities(std::vector<Box*> &box, const Player &player)
{
    int count{ 0 };
    for (const auto b : box)
    {
        if (b->getType() == 'u')
            if (b->getOwner() == player.getName())
                count++;
    }
    return count;
}

void displayRules()
{
    std::cout << "\n\n======================================================\n";
    std::cout << "\nThe object of the game is to become the wealthiest\n"
                 "player through buying, renting and selling property\n\n";
    std::cout << "Each player is given $1500\n\n";
    std::cout << "Players will take turns in the order they entered their names\n"
                 "and will roll the dices\n";
    std::cout << "Depending where they land on, they can buy an unowned property,\n"
                 "pay rent, taxes, draw a card or go to jail\n\n";
    std::cout << "If a player lands on an unowned property and he/she doesn't want\n"
                 "to buy it, the bank will sell it at auction to the highest bidder\n";
    std::cout << "Any player, including the one who refused to buy it in the first\n"
                 "place, can bid for the property\n";
    std::cout << "Bidding may start at any price\n\n";
    std::cout << "When you land on property owned by another player,\n"
                 "the owner collects rent from you in accordance with the list printed on\n"
                 "its Title Deed card.\n\n"
                 "If the property is mortgaged, no rent can be collected. When a\n"
                 "property is mortgaged, its Title Deed card is placed facedown in front\n"
                 "of the owner.\n\n"
                 "It is an advantage to hold all the Title Deed cards in a colorgroup\n (e.g., Rahova and Giulesti; or Colentina, Titan and\n"
                 "Tei) because the owner may then charge double rent\n"
                 "for unimproved properties in that color-group. This rule applies to\n"
                 "unmortgaged properties even if another property in that color-group is\n"
                 "mortgaged.\n\n"
                 "It is even more advantageous to have houses or hotels on properties\n"
                 "because rents are much higher than for unimproved properties.\n\n"
                 "The owner may not collect the rent if he/she fails to ask for it before\n"
                 "the second player following throws the dice.";
    std::cout << "\n\n======================================================\n\n";
}

void deletePlayer(std::string name, std::vector<Player> &players, std::vector<Box*> &box)
{
    for (auto &p : players)
    {
        if (p.getName() == name)
        {
            p.freeProperties(box);
            p.upForAuction(players, box);
            p.setName("");
            break;
        }
    }
}

bool payAmount(Player &player, double amount, std::vector<Box*> &box, std::vector<Player> &players)
{
    if (player.getMoney() >= amount)
    {
        player.modifyMoney(-amount);
        std::cout << "\nYou successfully paid $" << amount << std::endl;
        std::cout << "Money left - $" << player.getMoney() << std::endl;
    }
    else
    {
        if (player.notEnoughMoney(amount))
        {
            player.modifyMoney(-amount);
            std::cout << "\nYou successfully paid $" << amount << std::endl;
            std::cout << "Money left - $" << player.getMoney() << std::endl;
        }
        else
        {
            std::cout << "\nSorry, you don't have enough money to make your payment\n";
            std::cout << "You are out of the game\nYour properties will be put up to auction\n"
                         "All your houses will go back to the bank\n";
            deletePlayer(player.getName(), players, box);
            return false;
        }
    }
    return true;
}

int remainingPlayers(std::vector<Player> &players)
{
    int amount = 0;
    for (const auto &p : players)
    {
        if (!p.getName().empty())
            amount++;
    }
    return amount;
}