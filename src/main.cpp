// SPDX-License-Identifier: GPL-3.0-or-later

#include <raylib.h>

int main(int argc, char* argv[]) {
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);

    while (true) {
        if (WindowShouldClose()) {
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
