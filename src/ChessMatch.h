#pragma once
#include "ChessBot.h"
#include <memory>

enum class Winner {
    White,
    Black,
    Tie
};

class ChessMatch {
    std::shared_ptr<ChessBot> white;
    std::shared_ptr<ChessBot> black;

    thc::ChessRules game;

    size_t maxNumberOfMoves;
    size_t numberOfMoves = 0;

public:
    ChessMatch(std::shared_ptr<ChessBot> white, std::shared_ptr<ChessBot> black, size_t maxNumberOfMoves = 1000)
        : white(white), black(black), maxNumberOfMoves(maxNumberOfMoves) {}

    Winner PlayGame() {
        while (!GameIsOver() && numberOfMoves++ < maxNumberOfMoves) {
            thc::Move move;
            if (game.white) {
                move = white->GetBestMove(game);
            } else {
                move = black->GetBestMove(game);
            }
            game.PlayMove(move);
        }
        return GetWinner();
    }

    bool GameIsOver() {
        thc::TERMINAL terminal;
        game.Evaluate(terminal);
        return (terminal != thc::NOT_TERMINAL);
    }

    Winner GetWinner() {
        thc::TERMINAL terminal;
        game.Evaluate(terminal);
        if (terminal == thc::TERMINAL_BCHECKMATE || terminal == thc::TERMINAL_BSTALEMATE) {
            printf("%s : %s -> %s (White) (%ld)\n", white->GetName().c_str(), black->GetName().c_str(), white->GetName().c_str(), numberOfMoves);
            return Winner::White;
        } else if (terminal == thc::TERMINAL_WCHECKMATE || terminal == thc::TERMINAL_WSTALEMATE) {
            printf("%s : %s -> %s (Black) (%ld)\n", white->GetName().c_str(), black->GetName().c_str(), black->GetName().c_str(), numberOfMoves);
            return Winner::Black;
        } else {
            printf("%s : %s -> Tie (%ld)\n", white->GetName().c_str(), black->GetName().c_str(), numberOfMoves);
            return Winner::Tie;
        }
    }
};