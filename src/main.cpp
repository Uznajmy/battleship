// SPDX-License-Identifier: GPL-3.0-or-later

#include <raylib.h>
#include <raygui.h>
#include "assets.hpp"
#include "ui/UI.hpp"
#include "ui/pages/MainPage.hpp"

int main(int argc, char* argv[]) {
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);

    load_assets();

    UI ui(new MainPage());

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);
        ui.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
