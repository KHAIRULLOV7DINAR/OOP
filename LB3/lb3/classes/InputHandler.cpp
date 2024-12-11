#include "../headers/InputHandler.h"

InputHandler::InputHandler(){}


Coords InputHandler::CoordsInput(Player* human_player)
{
    int x_coord, y_coord;
    bool cin_flag = true;
    std::cout << "Enter the coordinates!" << std::endl;
    while(cin_flag)
    {
        std::cin >> x_coord;
        std::cin >> y_coord;

        if(std::cin.fail() || x_coord < 1 || y_coord < 1 || x_coord > human_player->GetGameField().GetWidth() || y_coord > human_player->GetGameField().GetHeight())
        {
            std::cin.clear(); // Сброс состояния cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cout << "Invalid coordinates! Please enter valid coordinates." << std::endl;
            continue;
        }
        cin_flag = false;
    }
    return Coords{x_coord, y_coord};
}


ShipOrientation InputHandler::OrientationInput(Player* human_player)
{
    ShipOrientation orientation;
    std::string string_orientation;
    std::cout << "Enter the orientation!" << std::endl;
    bool cin_flag = true;
    while(cin_flag)
    {
        std::cin >> string_orientation;

        if(string_orientation == "H")
        {
            orientation = ShipOrientation::Horizontal;
        }
        else if(string_orientation == "V")
        {
            orientation = ShipOrientation::Vertical;
        }
        else
        {
            std::cout << "Invalid orientation!" << std::endl;
            std::cin.clear(); // Сброс состояния cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            continue;
        }
        cin_flag = false;
    }
    return orientation;
}


std::string InputHandler::CommandInput(bool attack_flag, bool ability_flag)
{
    std::string command;
    bool cin_flag = true;
    while(cin_flag)
    {
        std::cin >> command;
        if(command == "UseAbility" && ability_flag)
        {
            return command;
        }
        else if(command == "UseAbility" && !ability_flag)
        {
            return "You already used 1 ability!";
        }
        else if(command == "Close")
        {
            return command;
        }
        else if(command == "Attack" && attack_flag)
        {
            return command;
        }
        else if(command == "Attack" && !attack_flag)
        {
            return "You already attacked an enemy!";
        }
        else if(command == "Pass" && attack_flag)
        {
            return "You should attack enemy!";
        }
        else if(command == "Pass" && !attack_flag)
        {
            return command;
        }
        else if(command == "Save")
        {
            return command;
        }
        else if(command == "Load")
        {
            return command;
        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
            std::cout << "Try again!" << std::endl;
            std::cin.clear(); // Сброс состояния cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            continue;
        }
        cin_flag = 0;
    }
}