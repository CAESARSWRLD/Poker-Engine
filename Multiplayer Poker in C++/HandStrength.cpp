#include "HandStrength.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>//for std:pair

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
	


	std::vector<int> hardCodedStraight = {
		4,5,6,7,8,9,10
	};


	//must include the play's cards and the board cards
	Card cardOne = player.getCardOne();
	Card cardTwo = player.getCardTwo();

	std::vector<Card> cards = board;
	cards.push_back(cardOne);
	cards.push_back(cardTwo);

	

	cout << findStraight(cards) << " high straight found" << endl;


	std::vector<Card> flushCards;
	
		Card newCard1 = Card(2, 1, true);
		Card newCard2 = Card(2, 1, true);
		Card newCard3 = Card(3, 1, true);
		Card newCard4 = Card(3, 1, true);
		Card newCard5 = Card(3, 1, true);
		Card newCard6 = Card(8, 1, true);
		Card newCard7 = Card(9, 1, true);

		flushCards.push_back(newCard1);
		flushCards.push_back(newCard2);
		flushCards.push_back(newCard3);
		flushCards.push_back(newCard4);
		flushCards.push_back(newCard5);
		flushCards.push_back(newCard6);
		flushCards.push_back(newCard7);

	


	cout << findFlush(flushCards) << " high flush found" << endl;


	int duplicateCount = 0;

	//returns the value of duplicates, if there are duplcaites. Also updates duplicate count to determine pair, trips or quads
	cout << findDuplicateCards(flushCards, duplicateCount) << " value pair found, with " << duplicateCount << " duplicates" << endl;
	cout << duplicateCount << endl;

	// should return an integer to represent hand strength, 
	// then players hand can be compared using the int returned by this function
	return 0;
}



int findQuads(std::vector<Card> cards)
{

	std::vector<std::pair<int, int>> cardsWithCount = {};

	
	for (size_t i = 0; i < cards.size(); i++)
	{
		int value = cards[i].getValue();
		bool alreadyCounted = false;

		for (auto& p : cardsWithCount)
		{
			if (p.first == value)
			{
				alreadyCounted = true;
				break;
			}
		}

		if (alreadyCounted)
			continue;

		int count = 0;
		for (size_t j = 0; j < cards.size(); j++)
		{
			if (cards[j].getValue() == value)
				count++;
		}

		std::pair<int, int> valueWithCount = std::pair(value, count);
		cardsWithCount.push_back(valueWithCount);
	}

	


	//finds most duplicated value
	int most = 0;
	for (auto& value : cardsWithCount)
	{
		if (value.second > most)
		{
			most = value.second;
		}
	}


	int valueOfMostDuped = -1;

	for (auto& value : cardsWithCount)
	{
		if (most == value.second)
		{
			valueOfMostDuped = value.first;
			break;
		}
	}

	return valueOfMostDuped;

}


int findFullHouse(std::vector<Card> cards)
{

	return 0;
}



// if players have the same high card of their flush, that will be handled outside of this function.
// this returns the highest card value of the flush
int findFlush(std::vector<Card> cards)
{

	

	int suitCounts[4] = { 0 };

	// count suits from the real cards
	for (int i = 0; i < cards.size(); i++)
	{
		suitCounts[cards[i].getSuit()]++;
	}

	int suitOfFlush = -1;

	for (int i = 0; i < 4; i++)
	{
		if (suitCounts[i] >= 5)
		{
			suitOfFlush = i;
			break;
		}
	}

	// no flush
	if (suitOfFlush == -1)
		return -1;

	int highestValue = -1;

	// find highest card of that suit (from test flush)
	for (auto& card : cards)
	{
		if (card.getSuit() == suitOfFlush && card.getValue() > highestValue)
		{
			highestValue = card.getValue();
		}
	}

	return highestValue;
}


// integer returned represents the highest card of the straight if there is a straight. If there isn't
// one, it'll return -1
int findStraight(std::vector<Card> cards)
{
	std::vector<int> hardCodedStraight = {
		5,6,7,8,9,11,12
	};

	std::vector<int> values;

	for (auto& card : cards)
	{
		values.push_back(card.getValue());
	}

	std::sort(values.begin(), values.end());



	values = hardCodedStraight;
	for (auto& val : values)
	{
		cout << val << endl;
	}

	//decrementing rather than incrementing makes it easier and probably faster to find the highest possible straight.
	//i also could've just sorted in descending order but this works too. 
	int trackConsecutive = 0;
	for (size_t i = values.size() - 1; i > 0; i--)
	{
		if (values[i] - 1 == values[i - 1])
		{
			while (i > 0 && values[i] - 1 == values[i - 1])
			{
				trackConsecutive++;

				if (trackConsecutive == 4)
				{
					//highest possible straight has been found
					return values[i + trackConsecutive - 1];
				}


				i--;
			}

			if (trackConsecutive < 4)
			{
				trackConsecutive = 0;
			}
		}
	}


	return -1;
}



int getBestPairValue()
{

	return 0;
}