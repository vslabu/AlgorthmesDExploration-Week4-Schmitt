#pragma once
#include "ChessBot.h"
#include <iostream>

class HumanPlayer : public ChessBot {
public:
    HumanPlayer() : ChessBot("Human") {}

    thc::Move GetBestMove(thc::ChessRules& game) override {
        printf("Current position:\n");
        printf("%s\n", game.ToDebugStr().c_str());

        printf("List of all legal moves in the current position\n");
        std::vector<thc::Move> moves;
        std::vector<bool> check;
        std::vector<bool> mate;
        std::vector<bool> stalemate;
        game.GenLegalMoveList(moves, check, mate, stalemate);
        unsigned int len = moves.size();
        for (unsigned int i = 0; i < len; i++) {
            thc::Move mv = moves[i];
            std::string mv_txt = mv.NaturalOut(&game);
            const char* suffix = "";
            if (check[i])
                suffix = " (note '+' indicates check)";
            else if (mate[i])
                suffix = " (note '#' indicates mate)";
            printf("%s%s / ", mv_txt.c_str(), suffix);
        }

        bool inputOk = false;
        while (!inputOk) {
            printf("\nEnter your move: ");
            std::string move;
            std::cin >> move;
            thc::Move mv;
            inputOk = mv.NaturalIn(&game, move.c_str());
            if (!inputOk) {
                printf("Invalid move\n");
            } else {
                return mv;
            }
        }
    }
};