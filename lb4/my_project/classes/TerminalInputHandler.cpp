#include "../headers/TerminalInputHandler.h"

TerminalInputHandler::TerminalInputHandler()
{
    string_commands["Attack"] = ATTACK;
    string_commands["Ability"] = ABILITY;
    string_commands["Save"] = SAVE;
    string_commands["Load"] = LOAD;
    string_commands["Exit"] = EXIT;
    string_commands["Input_ships"] = INPUT_SHIPS;
    string_commands["Pass"] = PASS;
}

void TerminalInputHandler::LoadCommands(const std::string& filename)
{
    try
    {
        FileWrapper file(filename, std::ios::in);

        std::set<char> assigned_keys;
        std::set<std::string> assigned_commands;

        std::string line;

        while (file.ReadLine(line))
        {
            
            std::istringstream iss(line);
            char key;
            std::string value;

            iss >> key >> value;

            if (assigned_keys.find(key) != assigned_keys.end())
            {
                throw std::runtime_error("Duplicate key assignment: " + std::string(1, key));
            }

            if (assigned_commands.find(value) != assigned_commands.end())
            {
                throw std::runtime_error("Duplicate command assignment: " + value);
            }

            if (string_commands.find(value) == string_commands.end())
            {
                throw std::runtime_error("Unknown command!");
            }

            commands_map[key] = string_commands[value];
            assigned_keys.insert(key);
            assigned_commands.insert(value);
        }
        if (commands_map.size() < string_commands.size())
        {
            throw std::runtime_error("Few commands!");
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        this->DefaultArguments();
    }
    
}

void TerminalInputHandler::DefaultArguments()
{
    std::vector<char> keys = {'1', '2', '3', '4', '5', '6', '7'};
    std::vector<std::string> values = {"Atack", "Ability", "Save", "Load", "Exit", "Input_ships", "Pass"};
    for (int i = 0; i < keys.size(); i++)
    {
        commands_map[keys[i]] = string_commands[values[i]];
    }
}

Command TerminalInputHandler::CommandInput()
{
    char x;
    std::cin >> x;
    if (commands_map.find(x) == commands_map.end())
    {
        return NONE;
    }
    return commands_map[x];
}


std::map<char, Command> TerminalInputHandler::GetMapOfCommands() const
{
    return commands_map;
}


Coords TerminalInputHandler::CoordsInput(int width, int height)
{
    int x_coord, y_coord;

    std::cin >> x_coord;
    std::cin >> y_coord;

    if(std::cin.fail() || x_coord < 1 || y_coord < 1 || x_coord > width || y_coord > height)
    {
        std::cin.clear(); // Сброс состояния cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
        throw InputException();
    }

    return Coords{x_coord, y_coord};
}


ShipOrientation TerminalInputHandler::OrientationInput()
{
    ShipOrientation orientation;
    std::string string_orientation;

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
        std::cin.clear(); // Сброс состояния cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
        throw InputException();
    }

    return orientation;
}