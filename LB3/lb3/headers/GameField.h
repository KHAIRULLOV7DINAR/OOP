#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <map>
#include <iostream>
#include <vector>
#include "Ship.h"
#include "FileWrapper.h"
#include "ShipManager.h"

struct FieldCell
{
  Ship* pShip;
  CellStatus status;
  int segIndex;
};

class GameField
{
private:
    int height;
    int width;

    std::vector<std::vector<FieldCell>> field;

public:
    GameField(int x, int y);
    GameField(const GameField &other);
    GameField(GameField &&other) noexcept;
    GameField& operator=(const GameField &other);
    GameField& operator=(GameField &&other) noexcept;
    ~GameField() {};

    int GetWidth() const;
    int GetHeight() const;
    const std::vector<std::vector<FieldCell>> GetField() const;
    const CellStatus GetStatus(Coords coords) const;

    
    void Create();

    void SetHeightWidth(int height, int width);
    bool IsValidCoordinate(Coords coords) const;
    void SetStatus(Coords cords, CellStatus status);
    bool CheckPlaceForShip(Coords coords);
    void AddShip(Ship &ship, Coords GivenCoords, ShipOrientation orientation);
    AttackResult Attack(Coords GivenCoords, bool DD_FLAG);
    void ShipSegmentRandomHitAttack(Coords given_coords);
    void Print();
    void PrintHidden() const;
    void SaveGameField(FileWrapper& file) const;
    void LoadGameField(FileWrapper& file);
    void UpdatePointers(ShipManager& ship_manager);
};





#endif