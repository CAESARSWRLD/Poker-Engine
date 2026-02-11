#include "Table.hpp"
#include <istream>

Table::Table(int playerCount) : betToCall(0.0), pot(0.0), smallBlind(1.0), bigBlind(2.0)
{
	

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




	system("cls");

	//std::cout << "Debug table created" << std::endl;
}

Table::Table() 
{
	
	isRunning = true;
	pot = 0.0;

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