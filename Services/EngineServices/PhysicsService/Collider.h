// Christopher Stackpole, 12/14/2025

#ifndef COLLIDER_H
#define COLLIDER_H

#include <variant>

#include <SFML/Graphics.hpp>

struct Circle
{
	float radius;
};

struct Rect
{
	sf::Vector2f half_axis;
};

using Collider = std::variant<Circle, Rect>;

#endif