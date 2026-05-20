#include <ship_generator.hpp>
#include <cstdlib>

void Ship::GenerateShip(int size, std::vector<Cell>& cells)
{
    //TO-DO: implement ship generation
}

bool Ship::isPartOfAShip(int posX, int posY)
{
    for(Cell& cell : shipCells)
    {
        if(cell.isIsPlacedOnGivenCoordinates(posX, posY)) return true;
    }
    return false;
}

void Ship::shoot(int posX, int posY)
{
    for(std::size_t i = 0; i < shipCells.size(); i++)
    {
        if(shipCells[i].isIsPlacedOnGivenCoordinates(posX, posY))
        {
            shipCells.erase(shipCells.begin() + i);
        }
    }
}

void GenerateEnemyShips(Board& board)
{
}