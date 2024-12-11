#include "../headers/Ship.h"

//------------
//CONSTRUCTORS
//------------

Ship::Ship(Lengths length) : Ship(length, Horizontal) {}

Ship::Ship(Lengths length, ShipOrientation orientation) : length(length), orientation(orientation)
{
    status = ShipStatus::Intact;
    head_coords = Coords{-1 ,-1};

    for (int i = 0; i < this->length; i++)
    {
        segments.push_back(ShipSegment{ShipSegmentStatus::Intact});
    }
}

//-----------
//GET_METHODS
//-----------

const std::vector<ShipSegment> Ship::GetSegments() const
{
    return segments;
}

Lengths Ship::GetLength() const
{
    return length;
}

const ShipOrientation Ship::GetOrientation() const
{
    return orientation;
}

ShipStatus Ship::GetStatus()
{
    return status;
}
//--------------
//SHIP_METHODS
//--------------

void Ship::SetOrientation(ShipOrientation orientation)
{
    this->orientation = orientation;
}

bool Ship::IsDestroyed() const
{
    for (auto seg : segments){
        if (seg.status != ShipSegmentStatus::Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::ShipStatusUpdate()
{
    
    if (this->IsDestroyed() && this->GetStatus() != ShipStatus::Destroyed){
        this->status = ShipStatus::Destroyed;
        return;
    }

    for (auto seg : segments){
        if (seg.status != ShipSegmentStatus::Intact)
        {
            this->status = ShipStatus::Damaged;
            return;
        }
    }
}


void Ship::DamageShipSegment(int index)
{
    if (segments[index].status == ShipSegmentStatus::Intact)
    {
        segments[index].status = ShipSegmentStatus::Damaged;
    }
    else if (segments[index].status == ShipSegmentStatus::Damaged)
    {
        segments[index].status = ShipSegmentStatus::Destroyed;
    }
    else if (segments[index].status == ShipSegmentStatus::Destroyed)
    {
        std::cout << "This ship segment is already destroyed";
    }

    this->ShipStatusUpdate();
}

void Ship::PrintShip() const
{
    
    std::cout << "Ship status is " << (this->IsDestroyed() ? "Destroyed" : "Intact") << '\n';
    std::cout << "Length of ship is " << segments.size() << '\n';
    std::cout << "Orientation of ship is " << ((orientation == ShipOrientation::Vertical) ? "Vertical" : "Horizontal") << "\n\n";

    for(auto seg : segments)
    {
        std::string word;
        switch (seg.status)
        {
            case ShipSegmentStatus::Intact:
                word = "Intact";
                break;
            case ShipSegmentStatus::Damaged:
                word = "Damaged";
                break;
            case ShipSegmentStatus::Destroyed:
                word = "Destroyed";
                break;
        }

        std::cout << "Status of segment is " << word << '\n';
    }
    std::cout << '\n';
}


void Ship::SetStatus(ShipStatus status)
{
    this->status = status;
}


void Ship::SetHeadCoords(Coords coords)
{
    head_coords.x = coords.x;
    head_coords.y = coords.y;
}


Coords Ship::GetHeadCoords()
{
    return head_coords;
}