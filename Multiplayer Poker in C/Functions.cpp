#include <iostream>
#include <string.h>
#include <chrono>
#include "Functions.hpp"
#include "Networking.hpp"
#include "VibeCodedFunctions.hpp"
#include "DebuggingTool.hpp"

static bool debugging = true;

void gameLoop()
{
	
	//Table table;

	//using int as input parameter means this is a debug table with default values
	Table table(6);
	
	int minimumPlayercount = 1;

	while(table.getPlayers().size() > minimumPlayercount)
	{
		std::cout << "New hand.\nPress enter to begin hand...";
		std::cin.get();
		std::cin.get();
		runHand(table);

		table.advancePositions();
		table.resetPlayersBetweenHands();
		table.setPot(0);
	}
}

void runHand(Table& table)
{
	size_t winningPlayerIndex = 0;
	
	//1 for preflop, 2 for turn and 3 for river
	int round = 1;
	double pot = 0;
	while(round <= 3)
	{
		std::cout << "ROUND " << round << std::endl;


		//runRound will return true when a player has won
		if (runRound(table, round, winningPlayerIndex, pot))
			break;
		
		

		table.setAllMadeActionsToFalse_withinHand();
		round++;
	}
	std::cout << "Hand is over with. Player " << table.getPlayers()[winningPlayerIndex].getName() << " has won\n";

	table.payTheWinner(table.getPlayers()[winningPlayerIndex]);

	//std::cout << table.getPlayers()[winningPlayerIndex].getName() << " has won\n";
}

void initializeTable(Table& table, double& pot)
{
	pot = table.getSmallBlind() + table.getBigBlind();

	table.getPlayers()[0].setCurrentBet(table.getSmallBlind());
	table.getPlayers()[0].reduceStackSizeBy(table.getSmallBlind());

	table.getPlayers()[1].setCurrentBet(table.getBigBlind());
	table.getPlayers()[1].reduceStackSizeBy(table.getBigBlind());

	table.setPot(pot);

	table.getPlayers()[1].setIsBB(true);
}

//this desperately needs refactoring at some point
bool runRound(Table& table, int round, size_t& winningPlayerIndex, double& pot)
{

	//DebuggingTool debug;
	bool bbOptionUsed = false;
	double currentTableBet = table.getBigBlind();

	if(round == 1)
	{
		initializeTable(table, pot);
	}

	

	//utg first to act preflop. sb first to act postflop
	size_t s = 2;
	if (round > 1)
		s = 0;



	size_t aggressingPlayerIndex = 1;
	while (1)
	{



		if (currentPlayerHasWon(table, winningPlayerIndex))
		{
			table.setPot(pot);

			std::cout << table.getPlayers()[winningPlayerIndex].getName() << " has won a pot of $" << pot << std::endl;
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

		
		if (curPlayer.getFolded())
		{
			++s;
			continue;
		}

		


		double currentPlayerPreviousBet = curPlayer.getCurrentBet();

		
		
		//SPECIAL CASE
		//bb option(if round equals 'preflop', player is bb and it limps/folds around)
		if (round == 1 && s == 1 && currentPlayerPreviousBet == currentTableBet && !bbOptionUsed)
		{
			bbOptionUsed = true;
			std::cout << "BB option\n";
			std::string action = facingCheckProcessAnswer(currentTableBet, pot);

			if (action == "check")
				break;
			else if (action == "bet")
			{
				aggressingPlayerIndex = s;
				table.setAllMadeActionsToFalse_withinHand();
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




		if (currentPlayerPreviousBet < currentTableBet)
		{
			std::cout << "If " << table.getPlayers()[s].getName() << " calls, they've already put in $" << table.getPlayers()[s].getCurrentBet() << std::endl;

			std::string action = facingBetProcessAnswer(currentTableBet, currentPlayerPreviousBet, pot);
			if (action == "fold")
			{
				curPlayer.setFolded(true);
			}
			else if (action == "raise")
			{
				aggressingPlayerIndex = s;

				table.setAllMadeActionsToFalse_withinHand();

				curPlayer.setCurrentBet(currentTableBet);

				curPlayer.reduceStackSizeBy(currentTableBet);
			}
			else
			{
				curPlayer.setCurrentBet(currentTableBet);
				curPlayer.reduceStackSizeBy(currentTableBet);

			}

			curPlayer.setMadeAction(true);

		}
		else if (currentPlayerPreviousBet == currentTableBet && aggressingPlayerIndex == s)
		{
			table.setPot(pot);

			// all other players called the current player's bet or it just checked around
			break;
		}
		else
		{
			

			std::string action = facingCheckProcessAnswer(currentTableBet, pot);


			if (action == "bet")
			{
				table.setAllMadeActionsToFalse_withinHand();
				curPlayer.setCurrentBet(currentTableBet);


				curPlayer.reduceStackSizeBy(currentTableBet);
			}

			curPlayer.setMadeAction(true);
		}

		table.setPot(pot);



		if (table.checkForEndOfRound())
		{
			break;
		}



		system("cls");
		++s;
	}

	std::cout << "END OF ROUND REACHED\n";
	std::cin.get();

	return false;
}

bool currentPlayerHasWon(Table& table, size_t& winnerIndex)
{
	size_t playersLeft = 0;
	size_t lastStanding = 0;

	for (size_t i = 0; i < table.getPlayerCount(); ++i)
	{
		if (!table.getPlayers()[i].getFolded())
		{
			playersLeft++;
			lastStanding = i;
		}
	}

	if (playersLeft == 1)
	{
		winnerIndex = lastStanding;
		return true;
	}

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
	
		std::cout << p.getName() << "[" << p.getStackSize() << "]    ";
	
		players++;

	}

	std::cout << std::endl;
	std::cout << "              sb          bb        utg                  \n";
	std::cout << std::endl;
	std::cout << "                  ********************************\n";
	std::cout << "              ****************************************\n";
	std::cout << "           **                                          **\n";
	std::cout << "         **                                              **\n";
	std::cout << "        **                                                **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                  pot: "<<table.getPot() << "                         **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "        **                                                 **\n";
	std::cout << "         **                                              **\n";
	std::cout << "           **                                          **\n";
	std::cout << "              ****************************************\n";
	std::cout << "                  ********************************\n";
	std::cout << "                            ";
	std::cout << std::endl;

	

	std::cout << "            ";



	if(players >= 4)
	{
		int count = 0;
		while (count < table.getPlayerCount())
		{

			if (count >= 4)
			{
				std::cout << table.getPlayers()[count].getName() << "[" << table.getPlayers()[count].getStackSize() << "]    ";
			}
			count++;
		}
	}
	



	std::cout << std::endl;
}


