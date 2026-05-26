// SPDX-License-Identifier: GPL-3.0-or-later

#include <raylib.h>
#include <raygui.h>
#include "ui/UI.hpp"
#include "ui/pages/MainPage.hpp"

int main(int argc, char* argv[]) {
    InitWindow(800, 600, "Battleship");
    Font font = GetFontDefault();
    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    SetTargetFPS(60);

    UI ui(new MainPage());

    while (true) {
        if (WindowShouldClose()) {
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        ui.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
