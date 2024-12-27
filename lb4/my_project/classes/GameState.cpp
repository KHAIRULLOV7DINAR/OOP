#include "../headers/GameState.h"

GameState::GameState(Player* human_player, AIPlayer* ai_player): human_player(human_player), ai_player(ai_player)
{
    current_round = 1;
}

FileWrapper& operator<<(FileWrapper& file, const GameState& game_state)
{
    try
    {
        file.write(game_state.current_round);
        file.write('\n');
        file.write(static_cast<int>(game_state.WIN_FLAG));
        file.write('\n');
        file.write(static_cast<int>(game_state.game_status));
        file.write('\n');

        file.write(static_cast<int>(game_state.attack_flag));
        file.write('\n');
        file.write(static_cast<int>(game_state.ability_flag));
        file.write('\n');
        file.write(static_cast<int>(game_state.turn_flag));
        file.write('\n');

        game_state.human_player->SavePlayer(file);
        game_state.ai_player->SavePlayer(file); 
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return file;
}

FileWrapper& operator>>(FileWrapper& file, GameState& game_state)
{
    int int_win_flag, int_game_status, int_current_round, int_attack_flag, int_ability_flag, int_turn_flag;
    try
    {
        file.read(int_current_round);

        file.read(int_win_flag);
        file.read(int_game_status);
        game_state.SetRoundNumber(int_current_round);
        game_state.WIN_FLAG = static_cast<bool>(int_win_flag);
        game_state.game_status = static_cast<bool>(int_game_status);

        file.read(int_attack_flag);
        file.read(int_ability_flag);
        file.read(int_turn_flag);

        game_state.attack_flag = static_cast<bool>(int_attack_flag);
        game_state.ability_flag = static_cast<bool>(int_ability_flag);
        game_state.turn_flag = static_cast<bool>(int_turn_flag);

        game_state.human_player->LoadPlayer(file);
        game_state.ai_player->LoadPlayer(file);
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return file;
}


bool GameState::GetFlag(int flag_number)
{
    switch(flag_number)
    {
        case 0:
            return WIN_FLAG;
            break;
        case 1:
            return game_status;
            break;
        case 2:
            return attack_flag;
            break;
        case 3:
            return ability_flag;
            break;
        case 4:
            return turn_flag;
            break;
        default:
            std::cout << "FLAG NOT FOUND!" << std::endl;
            return false;
            break;
    }
}

 
 void GameState::SetFlag(int flag_number, bool state)
 {
    switch(flag_number)
    {
        case 0:
            WIN_FLAG = state;
            break;
        case 1:
            game_status = state;
            break;
        case 2:
            attack_flag = state;
            break;
        case 3:
            ability_flag = state;
            break;
        case 4:
            turn_flag = state;
            break;
        default:
            std::cout << "FLAG NOT FOUND!" << std::endl;
            break;
    }
 }

void GameState::IncRoundNumber()
{
    round_number++;
}

void GameState::ResetRoundNumber()
{
    round_number = 1;
}

void GameState::SetRoundNumber(int number)
{
    round_number = number;
}

int GameState::GetRoundNumber()
{
    return round_number;
}

void GameState::ResetPlayers(Player* human_player, AIPlayer* ai_player)
{
    this->human_player = human_player;
    this->ai_player = ai_player;
}