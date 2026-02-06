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
	Card(int newVal, int newFace) : value(newVal), suit(newFace){}
	Card() : value(0), suit(0) {}

	int getValue()const
	{
		return value;
	}

	int getSuit()const
	{
		return suit;
	}

	std::string getName()
	{
		
		std::string vals[] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king" };
		std::string suits[] = { "clubs", "hearts", "diamonds", "spades" };

		std::string theName = vals[value] + " of " + suits[suit];

		return theName;
	}
};

