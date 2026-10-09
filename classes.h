#pragma once

#include <cmath>
#include <vector>
#include <raylib.h>
#include <optional>

inline constexpr int N = 500;
inline constexpr int R_V = 400;
inline constexpr int TPS = 100;
inline constexpr float pi = 3.1416f;


class Vec2 {
    public :
        float x, y;

        Vec2 ();
        Vec2 (float x, float y);

        Vec2 operator+ (const Vec2& other) const;
        Vec2 operator- (const Vec2& other) const;
        float operator* (const Vec2& other) const;
        Vec2 scalar_num_mul (const float num) const;
        float length () const;
        Vec2 normalize () const;
};


class Ray1 {
    public :
        Vec2 cords;
        std::vector <Vec2> points;
        int num;
        float angle;
        Vec2 direction;
        bool intersection;

        Ray1 ();
        Ray1 (Vec2 c, int n);

        void ray_update ();
        std::optional <Vec2> check_intersection (const Vec2& mirror_start, const Vec2& mirror_end) const;
        std::optional <Vec2> reflect (const Vec2& mirror_start, const Vec2& mirror_end);
};

inline constexpr int WIDTH = 1500, HEIGHT = 1000;
inline constexpr int text_width = 175, text_height = 20;
inline constexpr float lamp_x = 1000, lamp_y = 750;
inline Color background_color = {20, 20, 35, 255};
inline Color mirror_color = {0, 100, 255, 255};
inline Color ray_color = {255, 255, 75, 255};
// inline Color fps_text_color = {0, 255, 0, 255};

inline Vec2 mirror_start (600, 500);
inline Vec2 mirror_end = {700, 300};
inline float min_x = std::min (mirror_start.x, mirror_end.x);
inline float max_x = std::max (mirror_start.x, mirror_end.x);
inline float min_y = std::min (mirror_start.y, mirror_end.y);
inline float max_y = std::max (mirror_start.y, mirror_end.y);
inline bool isToggled = false;

void rays_check (std::vector <Ray1>& rays);
void rays_track ();