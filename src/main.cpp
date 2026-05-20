// SPDX-License-Identifier: GPL-3.0-or-later

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

std::vector<Pole> zaznaczonePola;
std::vector<Pole> trafionePola;

bool isZaznaczone(int x, int y) {
    for(auto& pole : zaznaczonePola)
    {
        if (pole.x == x && pole.y == y) return true;
    }
    return false;
}

bool isTrafione(int x, int y)
{
    for(auto& pole : trafionePola)
    {
        if(pole.x == x && pole.y == y) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);

    Statek s = Statek();
    s.pola = {Pole(1,2), Pole(1, 3), Pole(1,4)};

    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    while (true) {
        if (WindowShouldClose()) {
            break;
        }

        for(int x = 0; x < BOARD_SIZE_X; x++)
        {
            for(int y = 0; y < BOARD_SIZE_Y; y++)
            {
                std::string buttonText = "";
                if(isZaznaczone(x, y)) buttonText = "O";
                if(isTrafione(x, y)) buttonText = "X";
                if(GuiButton({RECT_POSITION_CHANGE_X * (x+1), RECT_POSITION_CHANGE_Y * (y+1), RECT_SIZE_X, RECT_SIZE_Y}, buttonText.c_str()))
                {
                    if(s.trafiony(x, y))
                    {
                        if(s.pola.size() == 0)
                        {
                            std::cout << "Gratulacje uzytkowniku, wygrales iPhone 10 Ultra Pro Max Limited Edition\n";
                        }
                        else {
                            std::cout << "Trafiles, ale nie zatopiles\n";
                        }
                        trafionePola.push_back(Pole(x,y));
                    }
                    zaznaczonePola.push_back(Pole(x, y));

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
