This is simple 2D Ray Tracer written in C++ with Raylib graphics library. It casts rays and reflects them from the mirror.

Rays are casting from point to circle equally. In code, N is number of rays, R_V is speed in pixels per second. TPS is tickrate. Framerate too.
Lamp_x, Lamp_y is point light source coordinates. Coordinates start in the left top of screen. X grows when we moving to the right, Y when we moving down.

Mirror is the section, defined by starting and ending point. Ray intersection with a mirror calculates by my own formula. It talks: let ray is the first function, mirror is the second one.
Task is simple: solve equation system and find functions intersection point.
