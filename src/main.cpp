#include <raylib.h>

int main(int argc, char **argv) {
    InitWindow(800, 600, "Echos");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Echos are coming after you...", 300, 300, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}