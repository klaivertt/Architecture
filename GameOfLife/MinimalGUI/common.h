#ifndef COMMON__H
#define COMMON__H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <format>

#define SCREEN_S sf::Vector2i(1920, 1080)

constexpr const float M_PI = 3.141592654f;

using Pixel = unsigned int;

class GameData;


bool CollisionRectPoint(sf::FloatRect& _rect, sf::Vector2f& _vec);
int Random(int _min, int _max);
void CenterTextOnShape(sf::Text& _text, const sf::Shape& _shape);
#endif