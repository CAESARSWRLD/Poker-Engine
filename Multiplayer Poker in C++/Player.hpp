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
	bool isBB;
	double currentBet;

	bool madeAction;
public:

	Player(std::string newName, double newStartingStack) : name(newName), stackSize(newStartingStack), cardOne(-1, -1), cardTwo(-1, -1), currentBet(0.0) {
		folded = false;
		madeAction = false;
		isBB = false;
	}

	void addToStack(double amountToadd)
	{
		stackSize += amountToadd;
	}

	void reduceStackSizeBy(double amountToReduceBy)
	{
		stackSize -= amountToReduceBy;
	}

	bool getMadeAction()const
	{
		return madeAction;
	}

	void setMadeAction(bool newMadeAction)
	{
		madeAction = newMadeAction;
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

	double getStackSize()const
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

	bool getIsBB()const
	{
		return isBB;
	}

	void setIsBB(bool bbBool)
	{
		isBB = bbBool;
	}
};