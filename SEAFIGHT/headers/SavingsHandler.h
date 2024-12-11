#ifndef SAVINGS_HANDLER_H
#define SAVINGS_HANDLER_H

#include <iostream>
#include "GameState.h"

class SavingsHandler
{
private:
public:
    SavingsHandler();

    void Save(const std::string& filename, const GameState& game_state);
    void Load(const std::string& filename, GameState& game_state);

    void WriteHash(const std::string& filename, FileWrapper& file_hash);
    int CountHash(const std::string& filename);
};

#endif