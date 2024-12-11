#include "../headers/SavingsHandler.h"

SavingsHandler::SavingsHandler(){}

void SavingsHandler::Save(const std::string& filename, const GameState& game_state)
{
    FileWrapper file(filename, std::ios::out | std::ios::trunc);
    file << game_state;

    FileWrapper file_hash("../my_project/hash_sum.txt", std::ios::out | std::ios::trunc);
    file.Rewind();
    WriteHash(filename, file_hash);
}

void SavingsHandler::Load(const std::string& filename, GameState& game_state)
{
    FileWrapper file(filename, std::ios::in);
    FileWrapper file_hash("../my_project/hash_sum.txt", std::ios::in);

    int hash_count = this->CountHash(filename);
    int hash_original;
    file_hash.read(hash_original);
    if (hash_original != hash_count)
    {
        throw std::runtime_error("Incorrect file!");
    }
    file.Rewind();

    file >> game_state;
}

void SavingsHandler::WriteHash(const std::string& filename, FileWrapper& file_hash)
{
    file_hash.write(this->CountHash(filename));
}

int SavingsHandler::CountHash(const std::string& filename){
    FileWrapper file_read(filename, std::ios::in);
    int hash = 0;
    int x = 0;
    int index = 1;
    bool while_flag;
    do
    {
        try
        {
            while_flag = file_read.read(x);
            hash += (x * (index % 10));
            index++;  
        }
        catch(std::exception& ex)
        {
            std::cout << "EOF" << std::endl;
            break;
        }
    }while (while_flag);

    return hash;
}