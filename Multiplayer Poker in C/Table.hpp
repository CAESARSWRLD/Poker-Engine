#pragma once
#include <vector>
#include <stdbool.h>
#include <string.h>
#include <deque>
#include <queue>

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

public:

	//this table constructor prompts the user for input. this constructor should be refactored when networking is added
	Table() {

		smallBlindIndex = 0;

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
			float startingStack;
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
				float startingStack;
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
		system("cls");
	}

	//debug(default) table. This table requires no input and creates default values for the table's attributes. Integer as lone parameter is the number of players
	Table(int playerCount)
	{

		while (playerCount > MAX_PLAYERS)
		{
			std::cout << "Debug table constructor has an integer value that is greater than the max # of players\nMax players at one table is " << MAX_PLAYERS << std::endl;
			std::cout << "Please enter a new number to represent the number of players at the table\n>";

			std::cin >> playerCount;
		}


		std::string a = "a";
		
		for (int i = 0; i < playerCount; i++)
		{
			a += "a";
			Player player(a, 100);
			addPlayer(player);
		}

		this->isRunning = true;

		system("cls");

		//std::cout << "Debug table created" << std::endl;
	}

	void advancePositions()
	{
		auto p = std::move(players.back());
		
		players.pop_back();

		players.push_front(std::move(p));
	}

	bool getIsRunning()const
	{
		return isRunning;
	}

	void setIsRunning()
	{
		isRunning = false;
	}

	std::deque<Player> getPlayers()const
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

	int getPlayerCount()const
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
};