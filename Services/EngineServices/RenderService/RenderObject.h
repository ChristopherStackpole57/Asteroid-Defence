// Christopher Stackpole, 12/07/2025

#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <SFML/Graphics.hpp>

struct RenderObject
{
	sf::Drawable* drawable;
	int layer = 0;
	bool active = true;
};

#endif