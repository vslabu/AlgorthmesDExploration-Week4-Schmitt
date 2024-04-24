#pragma once
#include "ChessBot.h"
#include <optional>

class RandomBot : public ChessBot {
public:
    RandomBot(std::optional<unsigned int> seed = std::nullopt) : ChessBot("RandomBot") {
        if (seed.has_value()) {
            srand(seed.value());
        } else {
            srand(static_cast<unsigned int>(time(nullptr)));
        }
    }

    thc::Move GetBestMove(thc::ChessRules& game) override {
        thc::MOVELIST moves;
        game.GenLegalMoveList(&moves);
        int random_move = rand() % moves.count;
        return moves.moves[random_move];
    }
};