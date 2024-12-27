#include "../headers/Game.h"


Game::Game(GameField& player_game_field, GameField& ai_player_game_field):player_game_field(player_game_field), ai_player_game_field(ai_player_game_field)
{
    human_player = new Player(ShipManager(2, {One, One}), AbilityManager(), player_game_field);
    ai_player = new AIPlayer(ShipManager(2, {One, One}), AbilityManager(), ai_player_game_field);
    game_state = new GameState(human_player, ai_player);
    savings_handler = new SavingsHandler();
}


Game::~Game()
{
    delete game_state;
    delete human_player;
    delete ai_player;
}


void Game::Reset()
{
    delete ai_player;
    ai_player_game_field.Create();
    ai_player = new AIPlayer(ShipManager(2, {One, One}), AbilityManager(), ai_player_game_field);
    if(!game_state->GetFlag(0))
    {
        delete human_player;
        player_game_field.Create();
        human_player = new Player(ShipManager(2, {One, One}), AbilityManager(), player_game_field);
    }
    game_state->ResetPlayers(human_player, ai_player);
}


void Game::PlacingShips(int amount_of_placed_ships, Coords coords, ShipOrientation orientation)
{
    human_player->PlaceShip(amount_of_placed_ships, coords, orientation);
}


void Game::AIPlacingShips()
{
    ai_player->AIRandomPlaceShip();
}


void Game::Save()
{
    savings_handler->Save(*game_state);
}


void Game::Load()
{
    savings_handler->Load(*game_state);
}


void Game::PlayerAttack(Coords coords)
{
    human_player->AttackEnemyField(coords, ai_player->GetGameField(), ai_player->GetShipManager());
    game_state->SetFlag(2, false);
}


void Game::AIPlayerAttack()
{
    ai_player->AIAttack(human_player->GetGameField(), human_player->GetShipManager());
}


void Game::PlayerUseAbility(Coords coords)
{
    human_player->ExecuteAbility(coords, ai_player->GetGameField(), ai_player->GetShipManager());
    game_state->SetFlag(3, false);
}


Player* Game::GetPlayer()
{
    return human_player;
}


GameState& Game::GetGameState()
{
    return *game_state;
}


AIPlayer* Game::GetAIPlayer()
{
    return ai_player;
}