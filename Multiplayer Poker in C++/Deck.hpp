#pragma once
#include "Card.hpp"
#include <array>
#include <string>
#include <iostream>
class Deck
{
private:
	std::vector<Card> cards;

public:
	Deck();
	void printDeck();
	Card getNextCard();


};