#pragma once
#include <random>
#include <cstdlib>
#include <string.h>

class Card
{
private:
	int value;
	int suit;
public:
	Card(int newVal, int newSuit) : value(newVal), suit(newSuit){}
	//suit 'f' for default
	Card() : value(0), suit('f') {}

	int getValue()const
	{
		return value;
	}

	char getSuit()const
	{
		return suit;
	}

	std::string getName()
	{
		
		std::string vals[] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king", "ace"};
		std::string suits[] = { "clubs", "hearts", "diamonds", "spades"  };

		std::string name = vals[value] + " of " + suits[suit];

		return name;
	}
};

