#include "classes.h"

int main () {
    SetConfigFlags (FLAG_MSAA_4X_HINT);
    InitWindow (WIDTH, HEIGHT, "C++ Raylib 2D Ray Tracing (MSAA 4x)");
    SetTargetFPS (TPS);

    rays_track ();

    CloseWindow ();
    return 0;
}