#pragma once
#include "thc.h"

class ChessBot {
    std::string name;

public:
    ChessBot(std::string name) : name(name) {}

    virtual thc::Move GetBestMove(thc::ChessRules& game) = 0;
    std::string& GetName() { return name; }
};