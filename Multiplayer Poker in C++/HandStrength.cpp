#include "HandStrength.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

int determineHandStrength(Player& player, Table& table)
{
	int strength = 0;
	std::vector<Card> cards;

	return strength;
}

bool findBestHand(Player& player, std::vector<Card> board)
{
	Card cardOne = player.getCardOne();
	Card cardTwo = player.getCardTwo();

	std::vector<Card> cards = board;
	board.push_back(cardOne);
	board.push_back(cardTwo);


	for (auto& card : cards)
	{
		cout << card.getName() << endl;
	}


	// should return an integer to represent hand strength, 
	// then players hand can be compared using the int returned by this function
	return 0;
}

int getBestPairValue()
{

	return 0;
}