#pragma once
#include "thc.h"
#include <map>

class Heuristic {
    std::string name;

public:
    Heuristic(std::string name) : name(name) {}

    virtual double EsitmateQualtiy(thc::ChessRules& game) = 0;
    std::string& GetName() { return name; }
};

// Evaluates moves based on the number of moves the opponent has after the move
class OpponentMobilityHeuristic : public Heuristic {
public:
    OpponentMobilityHeuristic() : Heuristic("Opponent Mobility") {}

    double EsitmateQualtiy(thc::ChessRules& game) override {
        thc::MOVELIST moves;
        game.GenLegalMoveList(&moves);
        double opponentMobility = moves.count;
        return 1 / opponentMobility;
    }
};

// Evaluates moves on the sum of the material values of the pieces
class MaterialHeuristic : public Heuristic {
    std::map<char, double> pieceValues = {
        {'P', 1},
        {'N', 3},
        {'B', 3},
        {'R', 5},
        {'Q', 9},
        {'K', 0},
        {'p', -1},
        {'n', -3},
        {'b', -3},
        {'r', -5},
        {'q', -9},
        {'k', 0}};

public:
    MaterialHeuristic() : Heuristic("Material") {}

    double EsitmateQualtiy(thc::ChessRules& game) override {
        double materialValue = 0;
        for (int squareIndex = 0; squareIndex < 64; squareIndex++) {
            char piece = game.squares[squareIndex];
            if (piece != ' ') {
                materialValue += (game.white ? -1 : 1) * pieceValues[piece];
            }
        }
        return materialValue;
    }
};

// Evaluates moves based on the number of pieces that are attacked by the opponent
class OpponentAttackHeuristic : public Heuristic {
public:
    OpponentAttackHeuristic() : Heuristic("OpponentAttack") {}

    bool IsSquareAttacked(thc::ChessRules& rules, int squareIndex) {
        // Create a list of opponent's legal moves
        thc::MOVELIST opponentMoves;
        rules.GenLegalMoveList(&opponentMoves);

        // Check if any opponent move targets the given square
        for (int i = 0; i < opponentMoves.count; i++) {
            auto& move = opponentMoves.moves[i];
            if (move.dst == squareIndex) {
                // Found a move that attacks the square
                return true;
            }
        }
        return false;
    }

    double EsitmateQualtiy(thc::ChessRules& game) override {
        double opponentAttack = 0;
        for (int squareIndex = 0; squareIndex < 64; squareIndex++) {
            char piece = game.squares[squareIndex];
            if (piece != ' ') {
                if (game.white) {
                    if (islower(piece)) {
                        opponentAttack += IsSquareAttacked(game, squareIndex);
                    }
                } else {
                    if (isupper(piece)) {
                        opponentAttack += IsSquareAttacked(game, squareIndex);
                    }
                }
            }
        }
        return 1 / opponentAttack;
    }
};