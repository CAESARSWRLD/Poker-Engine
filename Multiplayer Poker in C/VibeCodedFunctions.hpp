#include "Table.hpp"
#include "Player.hpp"
#include "Networking.hpp"
#include "Functions.hpp"

//These functions were created with genAI

//genAI preflop
void runPreflop_v(Table& table);

void runPreflop_v(Table& table)
{
    auto& players = table.getPlayers();
    size_t n = players.size();

    double pot = table.getSmallBlind() + table.getBigBlind();
    double currentTableBet = table.getBigBlind();

    players[0].setCurrentBet(table.getSmallBlind());
    players[1].setCurrentBet(table.getBigBlind());

    size_t current = 2;           // UTG
    size_t lastAggressor = 1;     // BB
    bool lastAggressorActed = false;
    size_t activePlayers = n;

    while (true)
    {
        Player& p = players[current];



        drawTable(table);

        std::cout << p.getName() << "'s turn\n\n";

        if (!p.getFolded())
        {
            double playerBet = p.getCurrentBet();
            std::string action;

            if (playerBet < currentTableBet)
            {
                action = facingBetProcessAnswer(currentTableBet, playerBet, pot);

                if (action == "fold")
                {
                    p.setFolded(true);
                    activePlayers--;
                }
                else if (action == "call")
                {
                    p.setCurrentBet(currentTableBet);
                }
                else if (action == "raise")
                {
                    currentTableBet = p.getCurrentBet();
                    lastAggressor = current;
                    lastAggressorActed = false;
                }
            }
            else
            {
                action = facingCheckProcessAnswer(currentTableBet, pot);

                if (action == "raise")
                {
                    currentTableBet = p.getCurrentBet();
                    lastAggressor = current;
                    lastAggressorActed = false;
                }
            }
        }

        system("cls");

        // mark if last aggressor has now acted
        if (current == lastAggressor)
            lastAggressorActed = true;

        if (activePlayers == 1)
            break;

        // advance to next active player
        do {
            current = (current + 1) % n;
        } while (players[current].getFolded());

        // only end once action returns to last aggressor AFTER they acted
        if (current == lastAggressor && lastAggressorActed)
            break;
    }
}




