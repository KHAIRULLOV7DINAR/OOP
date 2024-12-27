#include "../headers/GameController.h"


template <typename InputType, typename OutputType, typename RendererType>
GameController<InputType, OutputType, RendererType>::GameController(Game& game):game(game)
{
    input_handler = new InputType();
    game_display = new GameDisplay<RendererType, OutputType>();
}


template <typename InputType, typename OutputType, typename PaintType>
GameController<InputType, OutputType, PaintType>::~GameController()
{
    delete input_handler;
    delete game_display;
}


template <typename InputType, typename OutputType, typename PaintType>
bool GameController<InputType, OutputType, PaintType>::GameMenu()
{
    input_handler->LoadCommands("../my_project/commands.txt");
    bool flag_correct_command = false;

    game_display->Print("WELCOME TO THE GAME!");

    while (!flag_correct_command)
    {
        game_display->Print("CHOOSE AN OPTION!");
        Command command = input_handler->CommandInput();
        if (command == INPUT_SHIPS)
        {
            int amount_of_placed_ships = 0;
            while(amount_of_placed_ships != game.GetPlayer()->GetShipManager().GetAmountOfShips())
            {
                try
                {
                    game_display->Print("ENTER COORDINATES FOR PLACING SHIP!");
                    Coords coords = input_handler->CoordsInput(game.GetPlayer()->GetGameField().GetWidth(), game.GetPlayer()->GetGameField().GetHeight());
                    game_display->Print("ENTER ORIENTATION FOR SHIP!");
                    ShipOrientation orientation = input_handler->OrientationInput();
                    game.PlacingShips(amount_of_placed_ships, coords, orientation);
                    amount_of_placed_ships++;
                    game_display->PrintPlayerField(game.GetPlayer()->GetGameField());
                }
                catch(const std::exception& ex)
                {
                    std::cout << ex.what() << std::endl;
                }
            }
            flag_correct_command = true;
        }

        else if (command == LOAD)
        {
            try
            {
                game.Load();
                game_display->Print("LOAD IS SUCEED!");
                game_display->PrintPlayerField(game.GetPlayer()->GetGameField());
                game_display->PrintEnemyField(game.GetAIPlayer()->GetGameField());
                load_flag = true;
            }
            catch(const std::runtime_error& e)
            {
                std::cout << e.what() << '\n';
                continue;
            }
            flag_correct_command = true;
        }
        else if (command == EXIT)
        {
            game_display->Print("EXIT!");
            flag_correct_command = true;
            return false;
        }
        else
        {
            game_display->Print("INALID OPTION!");
        }
    }
    return true;

}

template <typename InputType, typename OutputType, typename PaintType>
void GameController<InputType, OutputType, PaintType>::StartGame()
{
    bool exit_flag = true;
    GameState& game_state = game.GetGameState();
    while(game_flag)
    {
        if(!game_state.GetFlag(0))
        {
            exit_flag = this->GameMenu();
        }

        if(!exit_flag)
        {
            return;
        }

        if(!load_flag)
        {
            game.AIPlacingShips();
            game_display->PrintPlayerField(game.GetAIPlayer()->GetGameField());
        }
        // load_flag = false;

        game_state.SetFlag(1, true);

        while(game_state.GetFlag(1))
        {
            this->PlayerTurn();
            if(!game_state.GetFlag(1))
            {
                break;
            }
            this->AIPlayerTurn();
        }
    }
}

template <typename InputType, typename OutputType, typename PaintType>
void GameController<InputType, OutputType, PaintType>::PlayerTurn()
{
    GameState& game_state = game.GetGameState();

    if(!load_flag)
    {
        game_state.SetFlag(2, true);
        game_state.SetFlag(3, true);
        game_state.SetFlag(4, true);
        load_flag = false;
    }

    Command command;
    game_display->Print("PLAYER'S TURN!");

    while(game_state.GetFlag(4))
    {
        game_display->Print("CHOOSE YOUR TURN OPTION!");

        command = input_handler->CommandInput();

        if(command == ABILITY)
        {
            if(!game_state.GetFlag(3))
            {
                game_display->Print("YOU ALREADY USED ABILITY!");
                continue;
            }

            try
            {
                game_display->Print("ENTER COORDINATES FOR ABILIITY!");
                Coords coords = input_handler->CoordsInput(game.GetPlayer()->GetGameField().GetWidth(), game.GetPlayer()->GetGameField().GetHeight());
                game.PlayerUseAbility(coords);
                game_state.SetFlag(3, false);
            }
            catch(std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }

            if(game.GetAIPlayer()->GetShipManager().GetAmountOfIntactShips() == 0)
            {
                game_state.SetFlag(4, false);
                break;
            }
        }
        else if(command == EXIT)
        {
            game_flag = false;
            game_display->Print("GAME IS CLOSED");
            exit(0);
            break;
        }
        else if(command == ATTACK)
        {
            if(!game_state.GetFlag(2))
            {
                game_display->Print("YOU ALREADY USED ATTACK!");
                continue;
            }
            try
            {
                game_display->Print("ENTER COORDINATES FOR ATTACK!");
                Coords coords = input_handler->CoordsInput(game.GetPlayer()->GetGameField().GetWidth(), game.GetPlayer()->GetGameField().GetHeight());
                game.PlayerAttack(coords);
                game_state.SetFlag(2, false);
                game_display->PrintEnemyField(game.GetAIPlayer()->GetGameField());
            }
            catch(std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                continue;
            }

            if(game.GetAIPlayer()->GetShipManager().GetAmountOfIntactShips() == 0)
            {
                game_state.SetFlag(4, false);
                break;
            }
        }
        else if(command == PASS)
        {
            if(game_state.GetFlag(2))
            {
                game_display->Print("YOU DIDN'T USE ATTACK!");
                continue;
            }
            game_state.SetFlag(2, false);
            game_state.SetFlag(3, false);
            game_display->Print("PLAYER'S TURN IS OVER!");
            break;
        }
        else if(command == SAVE)
        {
            game.Save();
            game_display->Print("SAVE IS SUCCEED!");
            continue;
        }
        else if(command == LOAD)
        {
            try
            {
                game.Load();
                game_display->Print("LOAD IS SUCEED!");
                game_display->PrintPlayerField(game.GetPlayer()->GetGameField());
                game_display->PrintEnemyField(game.GetAIPlayer()->GetGameField());
                continue;
            }
            catch(std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                continue;
            }
        }
        else
        {
            game_display->Print("INVALID COMMAND!");
            continue;
        }
        game_state.SetFlag(4, game_state.GetFlag(2) || game_state.GetFlag(3));

    }

    if(game.GetAIPlayer()->GetShipManager().GetAmountOfIntactShips() == 0)
    {
        game_display->Print("PLAYER HAS WON!");
        game_state.SetFlag(0, true);
        game_state.IncRoundNumber();
        game.Reset();
        game_state.SetFlag(1, false);
    }
}


template <typename InputType, typename OutputType, typename PaintType>
void GameController<InputType, OutputType, PaintType>::AIPlayerTurn()
{
    GameState& game_state = game.GetGameState();

    game_display->Print("AI_PLAYER'S TURN!");
    game.AIPlayerAttack();
    game_display->PrintPlayerField(game.GetPlayer()->GetGameField());
    if(game.GetPlayer()->GetShipManager().GetAmountOfIntactShips() == 0)
    {
        game_display->Print("AI_PLAYER HAS WON!");
        game_state.ResetRoundNumber();
        game_state.SetFlag(0, false);
        game.Reset();
        game_state.SetFlag(1, false);
    }
}

template class GameController<TerminalInputHandler, TerminalOutputHandler, FieldRenderer>;