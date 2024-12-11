#include "../headers/SavingsHandler.h"

SavingsHandler::SavingsHandler(){}

void SavingsHandler::Save(const GameState& game_state)
{
    FileWrapper file("../my_project/game.txt", std::ios::out | std::ios::trunc);
    file << game_state;

    FileWrapper file_hash("../my_project/hash_sum.txt", std::ios::out | std::ios::trunc);
    file.ResetIOPointer();
    WriteHash("../my_project/game.txt", file_hash);
}


void SavingsHandler::Load(GameState& game_state)
{
    FileWrapper file("../my_project/game.txt", std::ios::in);
    FileWrapper file_hash("../my_project/hash_sum.txt", std::ios::in);

    int hash_count = this->CountHash("../my_project/game.txt");
    int hash_check;
    file_hash.read(hash_check);
    if (hash_check != hash_count)
    {
        throw std::runtime_error("Incorrect file!");
    }
    file.ResetIOPointer();

    file >> game_state;
}

void SavingsHandler::WriteHash(const std::string& filename, FileWrapper& file_hash)
{
    file_hash.write(this->CountHash(filename));
}

int SavingsHandler::CountHash(const std::string& filename)
{
    FileWrapper file_read(filename, std::ios::in);
    int hash_sum = 0;
    int save_data = 0;
    int index = 1;
    bool while_flag;
    do
    {
        try
        {
            while_flag = file_read.read(save_data);
            hash_sum += (save_data * index);
            index++;  
        }
        catch(std::exception& ex)
        {
            std::cout << "EOF" << std::endl;
            break;
        }
    }while (while_flag);

    return hash_sum;
}