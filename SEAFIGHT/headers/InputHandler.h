#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <string>
#include <stdlib.h>

#include "Structures.h"
#include "Player.h"

class InputHandler
{
private:
public:
    InputHandler();

    Coords CoordsInput(Player* human_player);
    ShipOrientation OrientationInput(Player* human_player);
    std::string CommandInput(bool attack_flag, bool ability_flag);


};

#endif 