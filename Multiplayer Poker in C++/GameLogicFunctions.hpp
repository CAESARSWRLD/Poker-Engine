#pragma once
#include <stdbool.h>
#include <iostream>
#include "Table.hpp"
#include "Player.hpp"

void gameLoop();
void drawTable(Table& table);
void runHand(Table& table);
bool runRound(Table& table, int round, size_t& winningPlayerIndex, double& pot);
bool currentPlayerHasWon(Table& table, size_t& winnerIndex);
void initializeTable(Table& table, double& pot);
void roundLoop(Table& table, size_t& winningPlayerIndex, size_t& s, bool& bbOptionUsed, double& currentTableBet, int round);
void showPlayers(Table& table);
std::string correspondingStreet(int round);
Player& simpleRound(Table& table, double& pot);
bool runPreflop(Table& table, size_t& winningPlayerIndex, double& pot);
bool runPostflop(Table& table, size_t& winningPlayerIndex, double& pot);