#include <iostream>
#include <string.h>
#include <chrono>
#include "Functions.hpp"

void gameLoop()
{
	
	//Table table;

	//using int as input parameter means this is a debug table with default values
	Table table(8);
	
	
	while(table.getPlayers().size() > 1)
	{

		runHand(table);
		table.advancePositions();
	}
	
}


void runHand(Table& table)
{
	//index 0 of table.getPlayers() should always be the small blind
	


	std::cout << "\npreflop" << std::endl;

	
	
	
	
	for (size_t s = 0; s < table.getPlayers().size(); s++)
	{
		std::cout << table.getPlayers()[s].getName() << "'s turn. Select action\n";

	}	




	std::cin.get();

	std::cin.get();
	
		
}


void showPlayerOptions(std::string facingThisAction)
{
	if (facingThisAction == "bet or fold")
	{

	}
	else if (facingThisAction == "check")
	{

	}
}

void requestPlayerAction(int indexOfUTG)
{
	
}


//use until a real gui is added
void drawTable(Table& table)
{



	std::cout << "\n\n            ";
	int players = 0;
	for (auto& p : table.getPlayers())
	{

		//formatting text on screen
		if (players == 4)
			break;
	
		std::cout << p.getName() << "[" << p.getMoneyAmount() << "]    ";
	
		players++;

	}

	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "                  ********************************\n";
	std::cout << "              ****************************************\n";
	std::cout << "           **                                          **\n";
	std::cout << "         **                                              **\n";
	std::cout << "        **                                                **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "         **                                              **\n";
	std::cout << "           **                                          **\n";
	std::cout << "              ****************************************\n";
	std::cout << "                  ********************************\n";

	std::cout << std::endl;

	

	std::cout << "            ";



	if(players >= 4)
	{
		int count = 0;
		for (auto& p : table.getPlayers())
		{

			if (count >= 4)
			{
				//formatting text on screen
				std::cout << p.getName() << "[" << p.getMoneyAmount() << "]    ";
			}
			count++;
		}
	}
	



	std::cout << std::endl;
}


