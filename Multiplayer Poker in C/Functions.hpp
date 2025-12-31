#pragma once
#include <stdbool.h>
#include <iostream>
#include "Table.hpp"

void gameLoop();
void drawTable(Table& table);
void runHand(Table& table);
void requestPlayerAction(int indexOfUTG);
void showPlayerOptions(std::string facingThisAction);
