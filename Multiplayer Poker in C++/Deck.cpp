#include "Deck.hpp"
#include <random>
Deck::Deck()
{
	for (int value = 0; value < 13; ++value)
	{
		for (int suit = 0; suit <= 3; ++suit)
		{
			Card newCard = Card(value, suit);
			cards.push_back(newCard);
		}
	}
}


void Deck::printDeck()
{
	for (auto& card : cards)
	{
		std::cout << card.getName() << std::endl;
	}
}

//getting a new card from the deck for the board or a player
// should always be randomly selected from the deck right before the card
// is assigned to it's new position regardless of the deck being shuffled prior
// to the hand.
Card Deck::getNextCard()
{
	// 1. Obtain a non-deterministic seed from std::random_device
	std::random_device rd;

	// 2. Seed a Mersenne Twister engine with the random device
	// std::mt19937 is a widely used high-quality PRNG
	std::mt19937 mt(rd());

	// 3. Define a distribution (e.g., for a number between 1 and 100)
	std::uniform_int_distribution<int> dist(0, cards.size());

	std::cout << dist(mt) << " which is the card " << cards[dist(mt)].getName();






	return Card(0, 0);
}