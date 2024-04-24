#pragma once
#include "ChessBot.h"
#include "ChessMatch.h"
#include <map>
#include <vector>

struct CompetitionResult {
    int wins = 0, losses = 0, draws = 0;
};

class ChessCompetition {
    std::vector<std::shared_ptr<ChessBot>> bots;
    std::map<std::shared_ptr<ChessBot>, CompetitionResult> results;

public:
    ChessCompetition(std::vector<std::shared_ptr<ChessBot>> bots) : bots(bots) { PlayTournament(); }

    void PlayTournament() {
        for (auto& white : bots) {
            for (auto& black : bots) {
                ChessMatch match(white, black, 500);
                Winner winner = match.PlayGame();
                if (winner == Winner::White) {
                    results[white].wins++;
                    results[black].losses++;
                } else if (winner == Winner::Black) {
                    results[white].losses++;
                    results[black].wins++;
                } else {
                    results[white].draws++;
                    results[black].draws++;
                }
            }
            printf("\n");
        }

        for (auto& [bot, result] : results) {
            printf("%s: %d wins, %d losses, %d draws\n", bot->GetName().c_str(), result.wins, result.losses, result.draws);
        }
    }
};