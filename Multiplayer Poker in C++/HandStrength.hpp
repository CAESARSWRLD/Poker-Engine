#include "Card.hpp"
#include "Player.hpp"
#include "Table.hpp"
#include <iostream>
#include <string>

int determineHandStrength(Player& player, Table& table);
bool findBestHand(Player& player, std::vector<Card> board);
int getBestPairValue();
int findStraight(std::vector<Card> cards);
int findFlush(std::vector<Card> cards);
int findDuplicateCards(std::vector<Card> cards, int& value);
int findFullHouse(std::vector<Card> cards);


