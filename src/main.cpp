// SPDX-License-Identifier: GPL-3.0-or-later

#include <ctime>
#include <raylib.h>
#include<cstdlib>
#include <ship_generator.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <vector>



struct Pole {
    int x, y;
    Pole(int posX, int posY, bool statek = false)
    {
        x = posX;
        y = posY;
    }
    bool pressed = false;
    bool statek = false;
};

struct Statek {
    public:
    std::vector<Pole> pola;
    bool trafiony(int xPos, int yPos)
    {
        int i = 0;
        for(auto& pole : pola)
        {
            if(pole.x == xPos && pole.y == yPos)
            {
                pola.erase(pola.begin() + i);
                return true;
            }
            i++;
        }
        return false;
    }
};

int main(int argc, char* argv[]) {
    srand(time(NULL));
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);   

    Board gameBoard = Board();
    gameBoard.InitializeBoard();
    GenerateEnemyShips(gameBoard);
        
    Statek s = Statek();
    s.pola = {Pole(1,2), Pole(1, 3), Pole(1,4)};
    
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    while (true) {
        if (WindowShouldClose()) {
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        gameBoard.DrawBoard();
        
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
