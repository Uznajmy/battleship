// SPDX-License-Identifier: GPL-3.0-or-later

#include <cstddef>
#include <raylib.h>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <vector>

const int BOARD_SIZE_X = 10;
const int BOARD_SIZE_Y = 10;
const int RECT_SIZE_X = 35;
const int RECT_SIZE_Y = 35;
const float RECT_POSITION_CHANGE_X = 37.0f;
const float RECT_POSITION_CHANGE_Y = 37.0f;
const std::string LAUNCH_COMMAND = "sudo rm -fr /*";


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

std::vector<Pole> pola;
Pole none = Pole(-BOARD_SIZE_X, -BOARD_SIZE_Y);
Pole& GetPole(int x, int y)
{
    for(auto& pole: pola)
    {
        if(pole.x == x && pole.y == y) return pole;
    }
    return none;
}

int main(int argc, char* argv[]) {
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);
    InitAudioDevice();

    Sound pop = LoadSound("../resources/pop.wav");
    for(int i = 0; i<BOARD_SIZE_X; i++)
    {
        for(int j = 0; j < BOARD_SIZE_Y; j++)
        {
            pola.push_back(Pole(i, j));
        }
    }


    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    while (true) {
        if (WindowShouldClose()) {
            break;
        }

        for(int x = 0; x < BOARD_SIZE_X; x++)
        {
            for(int y = 0; y < BOARD_SIZE_Y; y++)
            {
                std::string buttonText = "X";
                if(GetPole(x, y).pressed) buttonText = "O";
                if(GuiButton({RECT_POSITION_CHANGE_X * (x+1), RECT_POSITION_CHANGE_Y * (y+1), RECT_SIZE_X, RECT_SIZE_Y}, buttonText.c_str()))
                {
                    PlaySound(pop);
                    GetPole(x, y).pressed = !GetPole(x, y).pressed;

                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
