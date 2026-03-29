#include "GameWrapper.hpp"
#include "NetworkSockets.h"
#include "Deck.hpp"
#include <random>


int main()
{
	
	sendInstruction("RAHH");

	GameWrapper gameWrapper;
	gameWrapper.menuLoop();
	
	return 0;
}