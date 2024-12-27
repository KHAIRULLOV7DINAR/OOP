#include "../headers/FieldRenderer.h"

void FieldRenderer::Print(GameField& game_field)
{
    int width = game_field.GetWidth();
    int height = game_field.GetHeight();

    std::cout<<"\n";
    for (int i = 0; i <= width; i++){
        std::cout << "--";
    }

    std::cout <<'\n';
    for (int y = 0; y < height; y++){
        std::cout << "| ";

        for (int x = 0; x < width; x++){
            switch (game_field.GetStatus(x, y))
            {
            case CellStatus::Ship:
                std::cout<< "\033[32m" <<"S "<< "\033[0m";
                break;
            case CellStatus::DamagedShip:
                std::cout << "\033[33m" << "H " << "\033[0m";
                break;
            case CellStatus::DestroyedShip:
                std::cout << "\033[31m" << "D " << "\033[0m";
                break;
            case CellStatus::SecretlyDamamged:
                std::cout << "\033[35m" << "H " << "\033[0m";
                break;
            case CellStatus::SecretlyDestroyed:
                std::cout << "\033[36m" << "H " << "\033[0m";
                break;
            case CellStatus::Empty:
                std::cout << "\033[30m" << "A " << "\033[0m";
                break;
            default:
                std::cout << "\033[34m" << "~ " << "\033[0m";
                break;
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void FieldRenderer::PrintHidden(GameField& game_field)
{
    int width = game_field.GetWidth();
    int height = game_field.GetHeight();

    std::cout<<"\n";
    for (int i = 0; i <= width; i++){
        std::cout << "--";
    }

    std::cout <<'\n';
    for (int y = 0; y < height; y++){
        std::cout << "| ";

        for (int x = 0; x < width; x++){
            switch (game_field.GetStatus(x, y))
            {
            case CellStatus::DamagedShip:
                std::cout << "\033[33m" << "H " << "\033[0m";
                break;
            case CellStatus::DestroyedShip:
                std::cout << "\033[31m" << "D " << "\033[0m";
                break;
            case CellStatus::SecretlyDamamged:
                std::cout << "\033[37m" << "H " << "\033[0m";
                break;
            case CellStatus::SecretlyDestroyed:
                std::cout << "\033[36m" << "H " << "\033[0m";
                break;
            case CellStatus::Empty:
               std::cout << "\033[34m" << "~ " << "\033[0m";
                break;
            default:
                std::cout << "\033[30m" << "U " << "\033[0m";
                break;
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}