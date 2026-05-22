// SPDX-License-Identifier: GPL-3.0-or-later

#include <raylib.h>
#include "ui/UI.hpp"
#include "ui/pages/MainPage.hpp"

UI ui(new MainPage());

int main(int argc, char* argv[]) {
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);

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
