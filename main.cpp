#include "classes.h"

int main () {
    SetConfigFlags (FLAG_MSAA_4X_HINT);
    InitWindow (WIDTH, HEIGHT, "C++ Raylib 2D Ray Tracing (MSAA 4x)");
    SetTargetFPS (TPS);

    Ray1 rays [N];
    for (int i = 0; i < N; i ++) {
        rays [i] = Ray1 (Vec2 (lamp_x, lamp_y), i);
        rays [i].points.emplace_back (Vec2 (lamp_x, lamp_y));
    }

    while (!WindowShouldClose ()) {
        BeginDrawing ();
        ClearBackground (background_color);

        DrawLineEx ({mirror_start.x, mirror_start.y}, {mirror_end.x, mirror_end.y}, 1, mirror_color);

        for (int i = 0; i < N; i ++) {
            rays [i].ray_update ();
            rays [i].points.emplace_back (Vec2 (rays [i].cords.x, rays [i].cords.y));

            if (rays [i].cords.x >= min_x && rays [i].cords.x <= max_x && rays [i].cords.y >= min_y && rays [i].cords.y <= max_y) {
                auto intersection_opt = rays [i].check_intersection (mirror_start, mirror_end);
                if (intersection_opt.has_value () && rays [i].intersection == false) {
                    Vec2 A = intersection_opt.value (); 
                    Vec2 D = {rays [i].cords.x, rays [i].cords.y}; 
                    float distance = (A - D).length ();

                    if (distance <= 5) {
                        rays [i].intersection = true;
                        rays [i].reflect (mirror_start, mirror_end);
                    }
                }
            }

            Vec2 start = {lamp_x, lamp_y};
            Vec2 end = {rays [i].cords.x, rays [i].cords.y};

            DrawLineStrip (reinterpret_cast <const Vector2*> (rays [i].points.data ()), size (rays [i].points), ray_color);
        }

        // string fps_text = "FPS: " + to_string (GetFPS ());
        // DrawText (fps_text.c_str (), 20, 20, 24, fps_text_color);
        DrawFPS (20, 20);
        EndDrawing ();
    }

    CloseWindow ();
    return 0;
}