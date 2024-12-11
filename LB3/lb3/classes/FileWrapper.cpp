#include "../headers/FileWrapper.h"

FileWrapper::FileWrapper(const std::string& filename, std::ios::openmode mode) : file(filename, mode)
{
    if (!file)
        throw std::runtime_error("File open failure");
}

FileWrapper::~FileWrapper()
{
    if (file.is_open())
        file.close();
}


template<>
void FileWrapper::write(const int& data)
{
    if (!file.is_open() || !file.good())
    {
        throw std::runtime_error("File not opened in output mode");
    }
    file << data;

    if (file.fail())
    {
        // Очистка состояния потока
        file.clear(); // Сбросить состояние потока
        throw std::runtime_error("Failed to write character to file");
    }
}

template<>
void FileWrapper::write(const char& data)
{
    if (!file.is_open() || !file.good())
    {
        throw std::runtime_error("File not opened in output mode");
    }
    file << data;

    if (file.fail())
    {
        // Очистка состояния потока
        file.clear(); // Сбросить состояние потока
        throw std::runtime_error("Failed to write character to file");
    }
}




template<>
bool FileWrapper::read(int& data) {
    if (!file.is_open() || !file.good()) {
        throw std::runtime_error("File not opened in input mode");
    }
    file >> data;

    if (file.fail())
    {
        // Очистка состояния потока
        file.clear(); // Сбросить состояние потока
        throw std::runtime_error("Failed to read integer from file");
    }
    return !file.eof();
}


void FileWrapper::ResetIOPointer()
{
    if (file.is_open())
    {
        file.seekp(0, std::ios::beg);
        file.seekg(0, std::ios::beg);
    }
}