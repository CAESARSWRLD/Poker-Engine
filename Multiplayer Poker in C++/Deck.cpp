#include "Deck.hpp"
#include <random>
Deck::Deck()
{
	for (int value = 0; value < 13; ++value)
	{
		for (int suit = 0; suit <= 3; ++suit)
		{
			Card newCard = Card(value, suit, false);
			cards.push_back(newCard);
		}
	}
}


void Deck::printDeck()
{
	int i = 0;
	for (auto& card : cards)
	{
		i++;
		std::cout << i << ") " << card.getName() << std::endl;
	}
}

// getting a new card from the deck for the board or a player
// should always be randomly selected from the deck right before the card
// is assigned to it's new position regardless of the deck being shuffled prior
// to the hand. Does this prevent cheating? I think it would help, but maybe I'm wrong
Card Deck::getNextCard()
{
	static std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, cards.size() - 1);

	while (true)
	{
		Card& card = cards[dist(mt)];

		if (!card.getUsed())
		{
			card.setUsed(true);
			return card;
		}
	}
}
