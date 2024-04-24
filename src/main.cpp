#include "ChessCompetition.h"
#include "HillClimbingBot.h"
#include "HumanPlayer.h"
#include "RandomBot.h"

int main() {
    std::vector<std::shared_ptr<ChessBot>> bots{
        std::make_shared<RandomBot>(),
        std::make_shared<HillClimbingBot>(std::make_shared<MaterialHeuristic>()),
        std::make_shared<HillClimbingBot>(std::make_shared<OpponentMobilityHeuristic>()),
        std::make_shared<HillClimbingBot>(std::make_shared<OpponentAttackHeuristic>())};

    ChessCompetition competition(bots);

    // std::shared_ptr<ChessBot> bot1 = std::make_shared<HumanPlayer>();
    // std::shared_ptr<ChessBot> bot2 = std::make_shared<HillClimbingBot>(std::make_shared<MaterialHeuristic>());
    // ChessMatch match2(bot1, bot2);
    // match2.PlayGame();

    return 0;
}