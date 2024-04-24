#pragma once
#include "ChessBot.h"
#include "Heuristic.h"
#include <iostream>
#include <limits>
#include <memory>

class HillClimbingBot : public ChessBot {
    std::shared_ptr<Heuristic> heuristic;

public:
    HillClimbingBot(std::shared_ptr<Heuristic> heuristicIn) : ChessBot("HillClimb:" + heuristicIn->GetName()), heuristic(heuristicIn) {}

    thc::Move GetBestMove(thc::ChessRules& game) override {
        thc::MOVELIST moves;
        game.GenLegalMoveList(&moves);
        double bestMoveValue = std::numeric_limits<double>::min();
        thc::Move bestMove;
        for (int i = 0; i < moves.count; i++) {
            auto& move = moves.moves[i];
            game.PushMove(move);
            double moveValue = heuristic->EsitmateQualtiy(game);
            game.PopMove(move);
            if (moveValue > bestMoveValue) {
                bestMoveValue = moveValue;
                bestMove = move;
            }
        }
        return bestMove;
    }
};