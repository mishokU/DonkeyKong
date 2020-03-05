#ifndef MAP_HPP
#define MAP_HPP

#include "SFML/Graphics.hpp"

constexpr int Height = 34;
constexpr int Width = 61;

constexpr int PixelPerCell = 16;
constexpr int WalkFrames = 3;
constexpr int ClimbFrames = 5;
constexpr int WalkWithWeaponFrames = 4;

extern sf::String tileMap[Height];

#endif //MAP_HPP
