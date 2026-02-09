#pragma once
#include <random>
#include <cstdlib>
#include <string.h>

class Card
{
private:
	int value;
	char suit;
public:
	Card(int newVal, char newSuit) : value(newVal), suit(newSuit){}
	//f for default
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
		
		std::string vals[] = { "zero", "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king", "ace"};
		char suits[] = { 'c', 'h', 'd', 's'};

		std::string name = vals[value] + " of " + suits[suit];

		return name;
	}
};

