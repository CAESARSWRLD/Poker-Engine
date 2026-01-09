#pragma once
#include "Card.hpp"
#include <string.h>
class Player
{
private:
	Card cardOne;
	Card cardTwo;
	std::string name;
	double stackSize;
	bool folded;
	bool myTurn;

	double currentBet;
public:

	Player(std::string newName, double newStartingStack) : name(newName), stackSize(newStartingStack), cardOne(-1, -1), cardTwo(-1, -1), currentBet(0.0) {
		folded = false;
		myTurn = false;
	}

	void setCurrentBet(double newBet)
	{
		currentBet = newBet;
	}

	double getCurrentBet()const
	{
		return currentBet;
	}

	std::string getName()const
	{
		return name;
	}

	double getMoneyAmount()const
	{
		return stackSize;
	}

	void setCards(Card one, Card two){
		cardOne = one;
		cardTwo = two;
	}

	bool getFolded()const
	{
		return folded;
	}

	void setFolded(bool newFolded)
	{
		folded = newFolded;
	}
};