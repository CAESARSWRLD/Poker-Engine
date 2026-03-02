#pragma once
#include <random>
#include <cstdlib>
#include <string.h>

class Card
{
private:
	int value;
	int suit;
	bool used;
public:
	Card(int newVal, int newSuit, bool newUsed) : value(newVal), suit(newSuit), used(newUsed){}
	//suit 'f' for default
	Card() : value(0), suit('f'), used(false){}

	int getValue()const
	{
		return value;
	}

	char getSuit()const
	{
		return suit;
	}

	//set to true when the card's been assigned to a position at the table
	void setUsed(bool newUsed)
	{
		used = newUsed;
	}

	bool getUsed()const
	{
		return used;
	}

	const std::string getName()
	{
		
		std::string vals[] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king", "ace"};
		std::string suits[] = { "clubs", "hearts", "diamonds", "spades"  };

		std::string name = vals[value] + " of " + suits[suit];

		return name;
	}
};

