#pragma once
#include "Card.hpp"
#include <string.h>
class Player
{
private:
	Card cardOne;
	Card cardTwo;
	std::string name;
	float stackSize;
	bool folded;
	bool myTurn;

	float currentBet;
public:
	Player(std::string newName, float newStartingStack) : name(newName), stackSize(newStartingStack), cardOne(-1, -1), cardTwo(-1, -1), currentBet(0.0) {
		folded = false;
		myTurn = false;
	}

	std::string getName()const
	{
		return name;
	}

	int getMoneyAmount()const
	{
		return stackSize;
	}

	void setCards(Card one, Card two){
		cardOne = one;
		cardTwo = two;
	}
};