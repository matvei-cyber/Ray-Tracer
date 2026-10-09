#include "classes.h"


// Class Vec2
Vec2::Vec2 () : x (0.0f), y (0.0f) {}
Vec2::Vec2 (float x, float y) : x (x), y (y) {}


Vec2 Vec2::operator+ (const Vec2& other) const {
    return Vec2 (x + other.x, y + other.y);
}

Vec2 Vec2::operator- (const Vec2& other) const {
    return Vec2 (x - other.x, y - other.y);
}

float Vec2::operator* (const Vec2& other) const {
    return (x * other.x) + (y * other.y);
}

Vec2 Vec2::scalar_num_mul (const float num) const {
    return Vec2 (x * num, y * num);
}

float Vec2::length () const {
    return sqrt ((x * x) + (y * y));
}

Vec2 Vec2::normalize () const {
    if (length () == 0) {
        return Vec2 (0.0f, 0.0f);
    }
    return Vec2 (x / length (), y / length ());
}


// Class Ray1
Ray1::Ray1 () : cords (0.0f, 0.0f), num (0), angle (0.0f), direction (0.0f, 0.0f), intersection (false) {}

Ray1::Ray1 (Vec2 c, int n) : cords (c), num (n) {
        angle = (2 * pi * num) / N;
        direction = Vec2 {std::cosf (angle), std::sinf (angle)}.normalize ();
        intersection = false;
}


void Ray1::ray_update () {
    cords = cords + direction.scalar_num_mul (R_V / TPS);
}

std::optional <Vec2> Ray1::check_intersection (const Vec2& mirror_start, const Vec2& mirror_end) const {
    Vec2 O = {lamp_x, lamp_y};
    Vec2 D = {lamp_x + direction.x, lamp_y + direction.y};
    Vec2 A = {mirror_start.x, mirror_start.y};
    Vec2 B = {mirror_end.x, mirror_end.y};

    if ((D.x - O.x) == 0 || (B.x - A.x) == 0) {
        return std::nullopt;
    }

    float k_OD = (D.y - O.y) / (D.x - O.x);
    float k_AB = (B.y - A.y) / (B.x - A.x);

    if (k_OD == k_AB) {
        return std::nullopt;
    }

    float line_intersection_x = (-D.y + (D.x * k_OD) + B.y - (B.x *  k_AB)) / (k_OD - k_AB);
    float line_intersection_y = (line_intersection_x * k_AB) + B.y - (B.x * k_AB);

    if (line_intersection_x >= min_x && line_intersection_x <= max_x && line_intersection_y >= min_y && line_intersection_y <= max_y) {
        return Vec2 (line_intersection_x, line_intersection_y);
    }
    return std::nullopt;
    }

std::optional <Vec2> Ray1::reflect (const Vec2& mirror_start, const Vec2& mirror_end) {
    Vec2 A = mirror_start;
    Vec2 B = mirror_end;
    Vec2 AB = B - A;

    Vec2 normal = Vec2 {AB.y, -AB.x}.normalize ();
    float ray_orientation = direction * normal;

    if (ray_orientation == 0) {
        return std::nullopt;
    } 
    
    if (ray_orientation > 0) {
        normal = Vec2 {-AB.y, AB.x}.normalize ();
    }

    Vec2 reflected_ray_direction = direction - normal.scalar_num_mul (2 * (direction * normal));
    direction = reflected_ray_direction;
    return std::nullopt;
}


// Other functions
void rays_check (std::vector <Ray1>& rays) {
    for (int i = 0; i < N; i ++) {
        if (isToggled == true) {
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
        }
        DrawLineStrip (reinterpret_cast <const Vector2*> (rays [i].points.data ()), size (rays [i].points), ray_color);
    }
}

void rays_track () {
    std::vector <Ray1> rays;
    for (int i = 0; i < N; i ++) {
        rays.emplace_back (Vec2 (lamp_x, lamp_y), i);
        rays [i].points.emplace_back (Vec2 (lamp_x, lamp_y));
    }

    while (!WindowShouldClose ()) {
        if (IsKeyPressed (KEY_SPACE)) {
            isToggled = !isToggled; 
        }

        BeginDrawing ();
        ClearBackground (background_color);

        DrawLineEx ({mirror_start.x, mirror_start.y}, {mirror_end.x, mirror_end.y}, 1, mirror_color);

        rays_check (rays);

        // string fps_text = "FPS: " + to_string (GetFPS ());
        // DrawText (fps_text.c_str (), 20, 20, 24, fps_text_color);
        DrawFPS (20, 20);
        EndDrawing ();
    }
}