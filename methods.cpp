#include "classes.h"


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


Ray1::Ray1 () : cords (0.0f, 0.0f), num (0) {}
Ray1::Ray1 (Vec2 c, int n) : cords (c), num (n) {}

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