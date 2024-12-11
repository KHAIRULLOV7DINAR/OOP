#include "../headers/Game.h"
Game::Game(GameField& player_game_field, GameField& ai_player_game_field):player_game_field(player_game_field), ai_player_game_field(ai_player_game_field)
{
    human_player = new Player(ShipManager(1, {One}), AbilityManager(), player_game_field);
    ai_player = new AIPlayer(ShipManager(1, {One}), AbilityManager(), ai_player_game_field);
    game_state = new GameState(human_player, ai_player);
    input_handler = new InputHandler();
    savings_handler = new SavingsHandler();
}


Game::~Game()
{
    delete game_state;
    delete human_player;
    delete ai_player;
}


void Game::StartGame()
{
    while(true)
    {
        std::cout << "New game has started!" << std::endl;
        std::cout << "Round number " << game_state->GetRoundNumber() << std::endl;
        if(!game_state->GetFlag(0))
        {
            this->PlacingShips();
        }
        this->AIPlacingShips();
        game_state->SetFlag(1, true);
        while(game_state->GetFlag(1))
        {
            this->PlayerTurn();
            if(!game_state->GetFlag(1))
            {
                break;
            }
            this->AIPlayerTurn();
        }
    }
}


void Game::Reset()
{
    delete ai_player;
    ai_player_game_field.Create();
    ai_player = new AIPlayer(ShipManager(1, {One}), AbilityManager(), ai_player_game_field);
    if(!game_state->GetFlag(0))
    {
        delete human_player;
        player_game_field.Create();
        human_player = new Player(ShipManager(1, {One}), AbilityManager(), player_game_field);
    }
}



void Game::PlacingShips()
{
    int amount_of_placed_ships = 0;

    std::cout << "Place your " << human_player->GetShipManager().GetAmountOfShips() << " ships with following sizes:";
    for(int index = 0; index < human_player->GetShipManager().GetAmountOfShips(); index++)
    {
        std::cout << human_player->GetShipManager().GetShip(index).GetLength() << ", ";
    }
    std::cout << std::endl;

    while(amount_of_placed_ships != human_player->GetShipManager().GetAmountOfShips())
    {
        try
        {
            Coords coords = input_handler->CoordsInput(human_player);
            ShipOrientation orientation = input_handler->OrientationInput(human_player);
            human_player->PlaceShip(amount_of_placed_ships, coords, orientation);
            amount_of_placed_ships++;
            human_player->PrintMyBoard();

        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

}


void Game::AIPlacingShips()
{
    ai_player->AIRandomPlaceShip();
    ai_player->PrintMyBoard();
}


void Game::PlayerTurn()
{
    game_state->SetFlag(2, true);
    game_state->SetFlag(3, true);
    game_state->SetFlag(4, true);

    std::string command;
    std::cout << "Player's turn!" << std::endl;

    while(game_state->GetFlag(4))
    {
        command = input_handler->CommandInput(game_state->GetFlag(2), game_state->GetFlag(3));
        if(command == "UseAbility")
        {
            try
            {
                human_player->ExecuteAbility(input_handler->CoordsInput(human_player), ai_player->GetGameField(), ai_player->GetShipManager());
                game_state->SetFlag(3, false);
                ai_player->PrintMyBoardHidden();
            }
            catch(std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                std::cin.clear(); // Сброс состояния cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            }

            if(ai_player->GetShipManager().GetAmountOfIntactShips() == 0)
            {
                game_state->SetFlag(4, false);
                break;
            }
        }
        else if(command == "Close")
        {
            std::cout << "Game is closed!" << std::endl;
            exit(0);
        }
        else if(command == "Attack")
        {
            try
            {
                human_player->AttackEnemyField(input_handler->CoordsInput(human_player), ai_player->GetGameField(), ai_player->GetShipManager());
                game_state->SetFlag(2, false);
                ai_player->PrintMyBoardHidden();
            }
            catch(std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                std::cin.clear(); // Сброс состояния cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            }

            if(ai_player->GetShipManager().GetAmountOfIntactShips() == 0)
            {
                game_state->SetFlag(4, false);
                break;
            }
        }
        else if(command == "Pass")
        {
            std::cout << "Player's turn is over!" << std::endl;
            break;
        }
        else if(command == "Save")
        {
            // game_state->Save("../my_project/game.txt");
            // std::cout << "Save is succeed" << std::endl;
            // continue;

            savings_handler->Save("../my_project/game.txt", *game_state);
            std::cout << "Save is succeed" << std::endl;
            continue;
        }
        else if(command == "Load")
        {
            // game_state->Load("../my_project/game.txt");
            // std::cout << "Load is succeed" << std::endl;
            // continue;

            try
            {
                savings_handler->Load("../my_project/game.txt", *game_state);
                std::cout << "Load is succeed" << std::endl;
                continue;
            }
            catch(std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }

        }
        else
        {
            std::cout << command << std::endl;
        }

        game_state->SetFlag(4, game_state->GetFlag(2) || game_state->GetFlag(3));
    }

    if(ai_player->GetShipManager().GetAmountOfIntactShips() == 0)
    {
        std::cout << "Player has won!" << std::endl;
        game_state->SetFlag(0, true);
        game_state->IncRoundNumber();
        this->Reset();
        game_state->SetFlag(1, false);
    }
}


void Game::AIPlayerTurn()
{
    std::cout << "Ai_player's turn!" << std::endl;
    ai_player->AIAttack(human_player->GetGameField(), human_player->GetShipManager());
    // ai_player->AttackEnemyField(Coords{1, 1}, human_player->GetGameField(), human_player->GetShipManager());
    human_player->PrintMyBoard();
    if(human_player->GetShipManager().GetAmountOfIntactShips() == 0)
    {
        std::cout << "AIPlayer has won!" << std::endl;
        game_state->ResetRoundNumber();
        game_state->SetFlag(0, false);
        this->Reset();
        game_state->SetFlag(1, false);
    }
}
