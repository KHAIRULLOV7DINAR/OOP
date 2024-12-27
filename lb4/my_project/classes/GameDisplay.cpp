#include "../headers/GameDisplay.h"

template <typename PaintType, typename OutputType>
GameDisplay<PaintType, OutputType>::GameDisplay()
{
    output = new OutputType();
    renderer = FieldRenderer();
}

template <typename PaintType, typename OutputType>
void GameDisplay<PaintType, OutputType>::PrintPlayerField(GameField& game_field)
{
    renderer.Print(game_field);
}

template <typename PaintType, typename OutputType>
void GameDisplay<PaintType, OutputType>::PrintEnemyField(GameField& game_field)
{
    renderer.PrintHidden(game_field);
}

template <typename PaintType, typename OutputType>
void GameDisplay<PaintType, OutputType>::PrintRound(int amount_of_rounds)
{
    output->PrintRound(amount_of_rounds);
}

template <typename PaintType, typename OutputType>
void GameDisplay<PaintType, OutputType>::Print(std::string message)
{
    output->PrintString(message);
}

template class GameDisplay<FieldRenderer, TerminalOutputHandler>;