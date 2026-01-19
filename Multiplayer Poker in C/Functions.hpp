#pragma once
#include <stdbool.h>
#include <iostream>
#include "Table.hpp"

void gameLoop();
void drawTable(Table& table);
void runHand(Table& table);
bool runRound(Table& table, int& round, Player*& winningPlayer);
bool aPlayerHasWon(Table& table);
