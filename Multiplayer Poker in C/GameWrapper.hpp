#pragma once
#include <iostream>
#include "Table.hpp"
#include "GameLogicFunctions.hpp"

class GameWrapper
{	
public:
	

	void menuLoop();
};

void GameWrapper::menuLoop()
{
	char choice = '\0';

	while(choice != 'j' && choice != 'h')
	{
		std::cout << "Join table or host table?\n(enter j or h):";
		std::cin >> choice;

		switch (choice)
		{
		case 'j':
			std::cout << "\nfeature not available\n";
			choice = '\0';
			break;
		case 'h':
			gameLoop();
			break;
		default:
			system("cls");
			break;
		}
	}
	
}

