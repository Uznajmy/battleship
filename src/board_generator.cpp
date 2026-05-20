#include <raylib.h>
#include <raygui.h>
#include <board_generator.hpp>
#include <string>
#include <iostream>

std::vector<Cell> boardCells;

Cell::Cell(int posX, int posY, bool isShip)
{
    x = posX;
    y = posY;
    isShipCell = isShip;
}

void Cell::placeShip() 
{
    isShipCell = true;
}

bool Cell::isIsPlacedOnGivenCoordinates(int xPos, int yPos)
{
    return xPos == x && yPos == y;
}

void Board::InitializeBoard()
{
    for(int x = 0; x < BOARD_SIZE_X; x++)
    {
        for(int y = 0; y < BOARD_SIZE_Y; y++)
        {
            AddCell(Cell(x, y));
        }
    }
}

void Board::DrawBoard()
{
    for(int x = 0; x < BOARD_SIZE_X; x++)
    {
        for(int y = 0; y < BOARD_SIZE_Y; y++)
        {
            Cell& cell = GetCellOnPosition(x, y);
            std::string buttonText;

            if(cell.wasPressed) buttonText = "O";
            if(cell.wasPressed && cell.isShipCell) buttonText = "X";

            float positionX = (RECT_SIZE_X + RECT_SEPERATION) * (x+1);
            float positionY = (RECT_SIZE_Y + RECT_SEPERATION) * (y+1);
            if(GuiButton({positionX, positionY, RECT_SIZE_X, RECT_SIZE_Y}, buttonText.c_str()) && !cell.wasPressed)
            {
                if(cell.isShipCell)
                {
                    std::cout << "pressed\n";
                    // Logic for ships handling
                }
                cell.wasPressed = true;
            }
            
        }
    }
}
