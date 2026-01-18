#include <iostream>
#include <string.h>
#include <chrono>
#include "Functions.hpp"
#include "Networking.hpp"
#include "VibeCodedFunctions.hpp"

void gameLoop()
{
	
	//Table table;

	//using int as input parameter means this is a debug table with default values
	Table table(6);
	
	int minimumPlayercount = 1;

	while(table.getPlayers().size() > minimumPlayercount)
	{
		runHand(table);

		//pops back and pushes front to change player positions/indexes in table.getPlayers(). This uses std::deque
		table.advancePositions();
	}
}

void runHand(Table& table)
{
	//1 for preflop, 2 for turn and 3 for river
	int round = 1;

	runRound(table, round);
	
	std::cin.get();
	std::cin.get();



	




	//std::cout << "end hand" << std::endl;

	//std::cin.get();

	//std::cin.get();
		
}

//this desperately needs refactoring at some point
bool runRound(Table& table, int& round)
{
	

	bool bbOptionUsed = false;
	

	

	//currentTableBet starts as the big blind amount
	double currentTableBet = table.getBigBlind();
	double pot = table.getSmallBlind() + table.getBigBlind();

	//index 0 of table.getPlayers() should always be the small blind
	// 
	//following lines set small and big blind current bet sizes to the size of the blinds already stored in the table

	table.getPlayers()[0].setCurrentBet(table.getSmallBlind());
	table.getPlayers()[1].setCurrentBet(table.getBigBlind());

	//utg first to act preflop. sb first to act postflop
	size_t s = 2;
	if (round != 1)
		s = 0;

	size_t aggressingPlayerIndex = 1;
	while (1)
	{
		if (aPlayerHasWon(table))
		{
			std::cout << "a player has won\n";

			return true;
		}

		//button reached. return to small blind
		if (s == table.getPlayers().size())
		{
			s = 0;
			system("cls");

			continue;
		}

		Player& curPlayer = table.getPlayers()[s];
		double currentPlayersBet = curPlayer.getCurrentBet();

		if (curPlayer.getFolded())
		{
			++s;
			continue;
		}
		
		//SPECIAL CASE
		//bb option(if round equals 'preflop', player is bb and it calls/folds around)
		if (round == 1 && s == 1 && currentPlayersBet == currentTableBet && !bbOptionUsed)
		{
			bbOptionUsed = true;
			std::cout << "BB option\n";
			std::string action = facingCheckProcessAnswer(currentTableBet, pot);

			if (action == "check")
				break;
			else if (action == "bet")
			{
				aggressingPlayerIndex = s;
				table.setAllMadeActionsToFalse();
				curPlayer.setCurrentBet(currentTableBet);
				curPlayer.setMadeAction(true);
				++s;
				system("cls");
				continue;
			}

		}

		//in the future add this: Player curPlayer = table.getPlayers()[s]
		

		std::cout << "Player index: " << s << " with player name: " << table.getPlayers()[s].getName() << std::endl;

		std::cout << "CURRENT BET SIZE " << currentTableBet << std::endl;
		//std::cout << "small: " << table.getPlayers()[0].getName() << " with $" << table.getPlayers()[0].getCurrentBet() << std::endl;
		//std::cout << "big: " << table.getPlayers()[1].getName() << " with $" << table.getPlayers()[1].getCurrentBet() << std::endl;
		std::cout << "POT: " << pot << std::endl;

		drawTable(table);
		std::cout << table.getPlayers()[s].getName() << "'s turn. Select action\n";

		std::cout << "Player " << table.getPlayers()[s].getName() << std::endl;




		if (currentPlayersBet < currentTableBet)
		{
			std::cout << "If " << table.getPlayers()[s].getName() << " calls, they've already put in $" << table.getPlayers()[s].getCurrentBet() << std::endl;

			std::string action = facingBetProcessAnswer(currentTableBet, currentPlayersBet, pot);
			if (action == "fold")
			{
				curPlayer.setFolded(true);
			}
			else if (action == "raise")
			{
				aggressingPlayerIndex = s;

				table.setAllMadeActionsToFalse();

				curPlayer.setCurrentBet(currentTableBet);
			}
			else
			{
				curPlayer.setCurrentBet(currentTableBet);
			}

			curPlayer.setMadeAction(true);

		}
		else if (currentPlayersBet == currentTableBet && aggressingPlayerIndex == s)
		{
			break;
		}
		else
		{
			

			std::string action = facingCheckProcessAnswer(currentTableBet, pot);


			if (action == "bet")
			{
				table.setAllMadeActionsToFalse();
				curPlayer.setCurrentBet(currentTableBet);

			}

			curPlayer.setMadeAction(true);
		}





		


		
		if (table.checkForEndOfRound())
		{
			break;
		}


		//std::cin.get();

		system("cls");
		++s;

	}

	std::cout << "END OF ROUND REACHED\n";
	std::cin.get();

	return false;
}

bool aPlayerHasWon(Table& table)
{
	int activePlayersCount = table.getPlayerCount();
	for (auto& player : table.getPlayers())
	{
		if (player.getFolded())
			activePlayersCount--;
	}

	if (activePlayersCount == 1)
		return true;

	return false;
}


//use until a proper ui is added
void drawTable(Table& table)
{



	std::cout << "\n\n            ";
	int players = 0;
	for (auto& p : table.getPlayers())
	{

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
				std::cout << p.getName() << "[" << p.getMoneyAmount() << "]    ";
			}
			count++;
		}
	}
	



	std::cout << std::endl;
}


