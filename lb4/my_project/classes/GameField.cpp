#include "../headers/GameField.h"

//------------
//CONSTRUCTORS
//------------

GameField::GameField(int x, int y) : width(x), height(y)
{
    if (x <= 0 || y <= 0)
    {
        throw std::invalid_argument("Invalid game field size values");
    }
    this->Create();
}

GameField::GameField(const GameField &other): width(other.width), height(other.height), field(other.field){}

GameField::GameField(GameField &&other) noexcept: width(other.width), height(other.height), field(std::move(other.field))
{
    other.height = 0;
    other.width = 0;
}

GameField &GameField::operator=(const GameField &other)
{
    if (this != &other)
    {
        width = other.width;
        height = other.height;
        field = other.field;
    }
    return *this;
}

GameField &GameField::operator=(GameField &&other) noexcept
{
    if (this != &other)
    {
        width = other.width;
        height = other.height;
        field = std::move(other.field);
        other.height = 0;
        other.width = 0;
    }
    return *this;
}


//-----------
//GET_METHODS
//-----------

int GameField::GetWidth() const
{
    return width;
}

int GameField::GetHeight() const
{
    return height;
}

const std::vector<std::vector<FieldCell>>* GameField::GetField() const
{
    return &field;
}

const CellStatus GameField::GetStatus(Coords coords) const
{
    return field[coords.y][coords.x].status;
}

//-----------
//FIELD_METHODS
//-----------

void GameField::Create()
{
  field.resize(height);
  for (int y = 0; y < height; y++) {
    field[y].reserve(width);
    for (int x = 0; x < width; x++) {
      field[y][x] = FieldCell{NULL, CellStatus::Unknown, 0};
    }
  }
}


void GameField::SetHeightWidth(int height, int width)
{
    this->height = height;
    this->width = width;
}


bool GameField::IsValidCoordinate(Coords coords) const
{
  return coords.y < height && coords.x < width && coords.x >= 0 && coords.y >= 0;
}

void GameField::SetStatus(Coords coords, CellStatus status)
{
  field[coords.y][coords.x].status = status;

  if(status == CellStatus::DamagedShip || status == CellStatus::DestroyedShip || status == CellStatus::SecretlyDamamged || status == CellStatus::SecretlyDestroyed)
  {
    field[coords.y][coords.x].pShip->DamageShipSegment(field[coords.y][coords.x].segIndex);
  }
}

bool GameField::CheckPlaceForShip(Coords coords)
{
  if (!this->IsValidCoordinate(coords))
    {
        throw OutOfBordersException();
    }

  int count = 0;
    for (int y = coords.y - 1; y <= coords.y + 1; y++)
    {
        for (int x = coords.x - 1; x <= coords.x + 1; x++)
        {
            if (x < 0 || y < 0 || x > width - 1|| y > height - 1)
            {
                count++;
            }
            else if (field[y][x].status != CellStatus::Ship)
            {
                count++;
            }
        }
    }
    return count == 9;
}


void GameField::AddShip(Ship &ship, Coords GivenCoords, ShipOrientation orientation)
{

  Coords coords{GivenCoords.x - 1, GivenCoords.y - 1};
  if (!this->IsValidCoordinate(coords))
  {
    throw OutOfBordersException();
  }

  std::vector<Coords> cells;
  bool flag = true;

  ship.SetOrientation(orientation);

  if (ship.GetOrientation() == Horizontal)
  {
      for (int i = 0; i < ship.GetLength(); i++)
      {
          if (CheckPlaceForShip({coords.x + i, coords.y}))
          {
              cells.push_back({coords.x + i, coords.y});
          }
          else
          {
            throw ShipCollisionException();
            flag = false;
            break;
          }
      }
  }
  else if (ship.GetOrientation() == Vertical)
  {
      for (int i = 0; i < ship.GetLength(); i++)
      {
          if (CheckPlaceForShip({coords.x, coords.y + i}))
          {
              cells.push_back({coords.x, coords.y + i});
          }
          else
          {
            throw ShipCollisionException();
            flag = false;
            break;
          }
      }
  }
  if (flag)
  {

    Ship* ptr_ship = &ship;
    ship.SetHeadCoords(cells[0]);
    int index = 0;

    for (Coords coordinate : cells)
    {
        field[coordinate.y][coordinate.x].pShip = ptr_ship;
        field[coordinate.y][coordinate.x].segIndex = index;
        index++;
        this->SetStatus(coordinate, CellStatus::Ship);
    }
  }else
  {
    std::cout << "Can't place the ship at these coordinates\n";
  }
}

AttackResult GameField::Attack(Coords GivenCoords, bool DD_FLAG)
{
  Coords coords{GivenCoords.x - 1, GivenCoords.y - 1};
  
  if(field[coords.y][coords.x].status == CellStatus::Unknown)
  {
    this->SetStatus(coords, CellStatus::Empty);
    return AttackResult::Nothing;
  }
  else if(field[coords.y][coords.x].status == CellStatus::Ship)
  {
    if(DD_FLAG)
    {
        field[coords.y][coords.x].pShip->DamageShipSegment(field[coords.y][coords.x].segIndex);
        this->SetStatus(coords, CellStatus::DestroyedShip);
        if(field[coords.y][coords.x].pShip->IsDestroyed())
        {
            return AttackResult::DDAndDestroyed;
        }
        return AttackResult::DD;
    }
    this->SetStatus(coords, CellStatus::DamagedShip);
    return AttackResult::Nothing;
  }
  else if(field[coords.y][coords.x].status == CellStatus::DamagedShip || field[coords.y][coords.x].status == CellStatus::SecretlyDamamged)
  {
    this->SetStatus(coords, CellStatus::DestroyedShip);
    if(field[coords.y][coords.x].pShip->IsDestroyed())
    {
        return AttackResult::Destroyed;
    }
    return AttackResult::Nothing;
  }else
  {
    throw AttackException();
  }
}


void GameField::ShipSegmentRandomHitAttack(Coords given_coords)
{
    if(field[given_coords.y][given_coords.x].status == CellStatus::Ship)
    {
        this->SetStatus(given_coords, CellStatus::SecretlyDamamged);
    }
    else if(field[given_coords.y][given_coords.x].status == CellStatus::SecretlyDamamged)
    {
        this->SetStatus(given_coords, CellStatus::SecretlyDestroyed);
    }
    else
    {
        given_coords.x++;
        given_coords.y++;
        this->Attack(given_coords, false);
    }
}

void GameField::Print()
{
    std::cout<<"\n";
    for (int i = 0; i <= width; i++){
        std::cout << "--";
    }

    std::cout <<'\n';
    for (int y = 0; y < height; y++){
        std::cout << "| ";

        for (int x = 0; x < width; x++){
            switch (field[y][x].status)
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

void GameField::PrintHidden() const
{
    std::cout<<"\n";
    for (int i = 0; i <= width; i++){
        std::cout << "--";
    }

    std::cout <<'\n';
    for (int y = 0; y < height; y++){
        std::cout << "| ";

        for (int x = 0; x < width; x++){
            switch (field[y][x].status)
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


void GameField::SaveGameField(FileWrapper& file) const
{
    file.write(this->GetHeight());
    file.write(' ');
    file.write(this->GetWidth());
    file.write('\n');

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            file.write(static_cast<int>(field[i][j].segIndex));
            file.write(' ');
            // file.write(static_cast<Ship*>(field[i][j].pShip));
            // file.write(' ');
            file.write(static_cast<int>(field[i][j].status));
            file.write(' ');
        }
        file.write('\n');
    }
}

void GameField::LoadGameField(FileWrapper& file)
{
    int load_height, load_width;
    file.read(load_height);
    file.read(load_width);
    this->SetHeightWidth(load_height, load_width);
    this->Create();


    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++)
        {
            int value;
            file.read(value);
            field[y][x].segIndex = value;
            file.read(value);
            if(value == 0)
            {
                field[y][x].status = CellStatus::Empty;
            }
            else if(value == 1)
            {
                field[y][x].status = CellStatus::Ship;
            }
            else if(value == 2)
            {
                field[y][x].status = CellStatus::DamagedShip;
            }
            else if(value == 3)
            {
                field[y][x].status = CellStatus::DestroyedShip;
            }
            else if(value == 5)
            {
                field[y][x].status = CellStatus::SecretlyDamamged;
            }
            else if(value == 6)
            {
                field[y][x].status = CellStatus::SecretlyDestroyed;
            }
            else
            {
                field[y][x].status = CellStatus::Unknown;
            }
        }
    }
}


void GameField::UpdatePointers(ShipManager& ship_manager)
{

    for(int ship_index = 0; ship_index < ship_manager.GetAmountOfShips(); ship_index++)
    {

        Ship* p_ship = &(ship_manager.GetShip(ship_index));

        Coords head_coords = ship_manager.GetShip(ship_index).GetHeadCoords();

        // std::cout << "head_coords" << std::endl;
        // std::cout << head_coords.x << std::endl;
        // std::cout << head_coords.y << std::endl;

        for (int segment_index = 0; segment_index < static_cast<int>(ship_manager.GetShip(ship_index).GetLength()); segment_index++)
        {
            // std::cout << std::endl << segment_index << std::endl << std::endl;
            if(ship_manager.GetShip(ship_index).GetOrientation() == ShipOrientation::Horizontal)
            {
                field[head_coords.y][head_coords.x + segment_index].pShip = p_ship;
            }
            else
            {
                field[head_coords.y + segment_index][head_coords.x].pShip = p_ship;
            }
        }
    }
}


CellStatus GameField::GetStatus(int x, int y)
{
    return field[y][x].status;
}
