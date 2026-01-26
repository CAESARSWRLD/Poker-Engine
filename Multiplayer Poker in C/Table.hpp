#pragma once
#include <vector>
#include <stdbool.h>
#include <string.h>
#include <deque>
#include <queue>
#include <string>

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
public:

	//this table constructor prompts the user for input. this constructor should be refactored when networking is added
	Table() {

		smallBlindIndex = 0;
		betToCall = 0.0;
		isRunning = true;

		int playersSoFar = 0;
		while (playersSoFar < 2)
		{
			system("cls");
			std::cout << "<PLAYERS>" << std::endl;
			
			for (auto& p : this->getPlayers())
			{
				//formatting text on screen
				if (playersSoFar > 1)
					std::cout << " | ";
				std::cout << p.getName();

			}

			std::cout << std::endl;

			std::string newUserName;
			std::cout << "***LOCAL GAME***\nCurrently there are " << players.size() << " players at the table\n" << "Enter a new player's name who you want to add to the table\n>";
			std::cin >> newUserName;
			double startingStack;
			std::cout << "$$$ Enter the buy in for this player $$$\n>";
			std::cin >> startingStack;
			Player newPlayer(newUserName, startingStack);

			this->addPlayer(newPlayer);
			playersSoFar++;

		}

		bool done = false;
		while (!done)
		{
			system("cls");


			std::cout << "<PLAYERS>" << std::endl;
			
			int playerCount = 0;
			for (auto& p : this->getPlayers())
			{
				playerCount++;

				//formatting text on screen
				if (playerCount > 1)
					std::cout << " | ";

				std::cout << p.getName();

			}
			


			std::cout << std::endl;

			std::string input;
			std::cout << "***Currently there are " << playerCount << " players at the table***\n";
			while (playerCount == MAX_PLAYERS)
			{
				std::cout << "\n***TABLE IS FULL WITH 8 PLAYERS***\nenter 2 to continue\n(2)Start game\n>";
				std::cin >> input;

				if (input == "2")
					return;//exits constructor
			}


			
			std::cout << "\nOptions\n(1)Add another player\n(2)Start game\n>";
			std::cin >> input;
			system("cls");

			if (input == "1")
			{


				std::cout << "<PLAYERS>" << std::endl;

				playerCount = 0;
				for (auto& p : this->getPlayers())
				{
					playerCount++;

					//formatting text on screen
					if (playerCount > 1)
						std::cout << " | ";

					std::cout << p.getName();

				}
				std::cout << std::endl;



				std::string newUserName;
				std::cout << "***Currently there are " << playerCount << " players at the table***\nEnter a new player's name who you want to add to the table\n>";
				std::cin >> newUserName;
				double startingStack;
				std::cout << "$$$ Enter the buy in for this player $$$\n>";
				std::cin >> startingStack;
				Player newPlayer(newUserName, startingStack);
				this->addPlayer(newPlayer);

			}
			else if (input == "2")
			{
				done = true;
			}
			else
			{

			}
			
		}

		std::cout << "Enter small blind as float\n>";
		std::cin >> smallBlind;
		system("cls");

		std::cout << "Now enter big blind as float\n>";
		std::cin >> bigBlind;


		system("cls");
	}

	//debug(default) table. This table requires no input and creates default values for the table's attributes. Integer as lone parameter is the number of players
	Table(int playerCount)
	{
		betToCall = 0.0;

		while (playerCount > MAX_PLAYERS)
		{
			std::cout << "Debug table constructor has an integer value that is greater than the max # of players\nMax players at one table is " << MAX_PLAYERS << std::endl;
			std::cout << "Please enter a new number to represent the number of players at the table\n>";

			std::cin >> playerCount;
		}


		std::string a = "a";
		
		for (int i = 0; i < playerCount; ++i)
		{
			std::string name = "p" + std::to_string(i);
			Player player(name, 100);
			
			
			addPlayer(player);
		}

		this->isRunning = true;

		this->smallBlind = 1.0;
		this->bigBlind = 2.0;


		system("cls");

		//std::cout << "Debug table created" << std::endl;
	}

	//sets all madeAction booleans of table's active players to false. Make sure to set the aggressing player's madeAction to true after this is called. Used when a player bets or rasies
	void setAllMadeActionsToFalse()
	{

		for (auto& player : players)
		{
			if(!player.getFolded())
				player.setMadeAction(false);
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
};