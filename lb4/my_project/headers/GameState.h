#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "AIPlayer.h"
#include "FileWrapper.h"

class GameState
{
private:
    bool WIN_FLAG = false;
    int round_number = 1;
    bool game_status = true;

    bool attack_flag = true;
    bool ability_flag = true;
    bool turn_flag = true;

    Player* human_player;
    AIPlayer* ai_player;
    int current_round;

public:
    GameState(Player* human_player, AIPlayer* ai_player);
    friend FileWrapper& operator<<(FileWrapper& file, const GameState& state);
    friend FileWrapper& operator>>(FileWrapper& file, GameState& state);
    bool GetFlag(int flag_number);
    void SetFlag(int flag_number, bool state);
    void IncRoundNumber();
    void ResetRoundNumber();
    void SetRoundNumber(int number);
    int GetRoundNumber();
    void ResetPlayers(Player* human_player, AIPlayer* ai_player);
};

#endif
