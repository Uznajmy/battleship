#include <raylib.h>
#include <raygui.h>
#include <vector>

const int BOARD_SIZE_X = 10;
const int BOARD_SIZE_Y = 10;
const float RECT_SIZE_X = 35.0f;
const float RECT_SIZE_Y = 35.0f;
const float RECT_SEPERATION = 2.0f;


// x & y values should be removed in the near future, because you can just use two-dimensional list
struct Cell {
        int x, y;
        bool isShipCell = false;
        bool wasPressed = false;
        Cell(int posX, int posY, bool isShip = false);
        void placeShip();
        bool isIsPlacedOnGivenCoordinates(int xPos, int yPos);
};

struct Board {
    private:
        std::vector<Cell> boardCells;
        Cell nullCell = Cell(-BOARD_SIZE_X, -BOARD_SIZE_Y);
    public:
        Cell& GetCellOnPosition(int xPos, int yPos)
        {
            for(Cell& cell : boardCells)
            {
                if(cell.isIsPlacedOnGivenCoordinates(xPos, yPos)) return cell;
            }
            return nullCell;
        }
        void AddCell(Cell cell)
        {
            boardCells.push_back(cell);
        }

        std::vector<Cell>& GetCells() 
        {
            return boardCells;
        }

        void InitializeBoard();
        void DrawBoard();
};


