#ifndef FIELD_RENDERER
#define FIELD_RENDERER

#include <iostream>
#include "GameField.h"

class FieldRenderer{
public:
    FieldRenderer() = default;

    void Print(GameField& game_field);
    void PrintHidden(GameField& game_field);
};

#endif