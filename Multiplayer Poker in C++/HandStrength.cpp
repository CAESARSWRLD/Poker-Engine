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

	cout << findFlush(cards) << " high flush found" << endl;




	// should return an integer to represent hand strength, 
	// then players hand can be compared using the int returned by this function
	return 0;
}



// if players have the same high card of their flush, that will be handled outside of this function.
// this returns the highest card value of the flush
int findFlush(std::vector<Card> cards)
{ 

	
	std::vector<Card> flushCards;

	for (int i = 0; i < 7; i++)
	{
		Card newCard = Card(i, 1, true);
		flushCards.push_back(newCard);
		cout << "card: " << newCard.getName() << endl;

		cout << "it has the suit " << newCard.getSuit() << endl;
	}

	int suitCounts[4] = {};
	for (int i = 0; i < flushCards.size(); i++)
	{
		suitCounts[flushCards[i].getSuit()]++;

		cout << flushCards[i].getSuit() << " is the suit" << endl;
	}

	int suitOfFlush = -1;
	for (size_t i = 0; i < flushCards.size(); i++)
	{
		if (suitCounts[i] >= 5)
		{
			cout << "FLUSH FOUND" << endl;
			suitOfFlush = i;
			cout << "suit of flush is " << suitOfFlush << endl;
			
			break;
		}
		return -1;
	}

	int highestValue = -1;
	//find highest value card of flush
	for (auto& card : flushCards)
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