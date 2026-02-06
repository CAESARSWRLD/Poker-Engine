#pragma once
#include <vector>
#include <stdbool.h>
#include <string.h>
#include <deque>
#include <queue>
#include <string>
#include <iostream>
#include "Player.hpp"
#include "Card.hpp"

constexpr int MAX_PLAYERS = 8;

class Table
{
private:
	std::deque<Player> players;
	Card cards[52];
	int tableID = 0;
	bool isRunning;
	int smallBlindIndex;
	double smallBlind;
	double bigBlind;
	double betToCall;
	double pot;
public:


	//this table constructor prompts the user for input. 
	// this constructor should be refactored when networking is added
	Table();

	//debug(default) table. This table requires no input and creates default 
	//values for the table's attributes. Integer as lone parameter is the number of players
	Table(int playerCount);
	

	void resetPlayerBetSizes()
	{
		for (auto& p : players)
		{
			p.setCurrentBet(0);
		 }
	}

	void addToPot(double addedToPot)
	{
		pot += addedToPot;
	}
	
	void setPot(double newPotAmount)
	{
		pot = newPotAmount;
	}

	void payTheWinner(Player& winner, double amount)
	{
		winner.addToStack(amount);
		
	}

	double getPot()const
	{
		return pot;
	}

	//sets all madeAction booleans of table's active players to false. Make sure to set the aggressing player's madeAction to true after this is called. Used when a player bets or rasies
	void setAllMadeActionsToFalse_withinHand()
	{

		for (auto& player : players)
		{
			if(!player.getFolded())
				player.setMadeAction(false);
		}
	}

	void resetPlayersBetweenHands()
	{

		for (auto& player : players)
		{
				player.setMadeAction(false);
				player.setFolded(false);
		}
	}

	bool checkForEndOfRound()
	{
		//std::cout << "entered check func\n";
		//std::cin.get();
		for (auto& p : players)
		{
			//round cannot end if there's a player who hasnt made their action 
			if (p.getMadeAction() == false || p.getFolded() == false)
			{
				//std::cout << "WE MADE IT HERE\n";
				//std::cin.get();
				return false;
			}
		}
		//std::cout << "CHECKED AND RETURNED TRUUUE\n";
		//std::cin.get();
		return true;
	}

	double getSmallBlind()const
	{
		return smallBlind;
	}

	double getBigBlind()const
	{
		return bigBlind;
	}

	//after each hand this runs to shift the positions of players at the table
	void advancePositions()
	{
		auto p = std::move(players.front());
		
		players.pop_front();

		players.push_back(std::move(p));
	}

	bool getIsRunning()const
	{
		return isRunning;
	}

	void setIsRunning()
	{
		isRunning = false;
	}

	std::deque<Player>& getPlayers()
	{
		return players;
	}
		
	bool addPlayer(Player& player)
	{
		if (getPlayerCount() == MAX_PLAYERS) {
			std::cout << "Max player limit reached" << std::endl;
			return false;
		}

		
		players.push_back(player);
		return true;
	}

	size_t getPlayerCount()const
	{
		return players.size();
	}

	void setSmallBlindIndex(int index)
	{
		smallBlindIndex = index;
	}

	int getSmallBlindIndex()const
	{
		return smallBlindIndex;
	}

	size_t getIndexOfFirstToAct()
	{
		size_t index = -1;
		for (size_t i = 0;i < getPlayerCount(); ++i)
		{
			if (!players[i].getFolded())
			{
				index = i;
				break;
			}
		}


	}

	bool foldedToBB()
	{
		int count = 0;
		for (Player& player : players)
		{
			if (player.getIsBB())
				continue;
			if (player.getFolded() && !player.getIsBB())
				count++;
		}

		if (count == getPlayerCount() - 1)
			return true;

		return false;
	}
};