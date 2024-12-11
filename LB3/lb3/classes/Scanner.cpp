#include "../headers/Scanner.h"

Scanner::Scanner(GameField& field, Coords coords):field(field), coords(coords){}

int Scanner::UseAbility()
{
    for (int y_coordinate = coords.y - 1; y_coordinate < coords.y + 1; y_coordinate++)
    {
        for (int x_coordinate = coords.x - 1; x_coordinate < coords.x + 1; x_coordinate++)
        {
            if (!field.IsValidCoordinate(Coords{x_coordinate, y_coordinate}))
            {
                throw OutOfBordersException();
            }
            else if(field.GetStatus(Coords{x_coordinate, y_coordinate}) == CellStatus::Ship)
            {   
                std::cout << "YES" << std::endl;
                return 1;
            }
                
        }
    }
    std::cout << "NO" << std::endl;
    std::cout << "Scanner was used!" << std::endl;
    return 1;
}