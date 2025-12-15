// Christopher Stackpole, 12/13/2025

#ifndef SWORD_H
#define SWORD_H

#include <cfloat>
#include <cmath>
#include <iostream>
#include <memory>

#include "Services.h"
#include "Services/GameServices/AsteroidService/AsteroidService.h"
#include "Services/GameServices/PoolService/PoolService.h"

#include "GameObjects/GameObjectInterface.h"
#include "GameObjects/Asteroid.h"

class SWORD : public IGameObject
{
public:
	SWORD();

	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;

	void SetPosition(sf::Vector2f position) override;
	sf::Vector2f GetPosition() override;
	void SetRotation(sf::Angle angle);
	sf::Angle GetRotation();
	sf::Vector2f GetSize() override;
private:
	bool debounce = false;
	int shot_time = 0;
	int fire_rate = 20;
	float rangesq = 200000;
	float laser_speed = 500.f;

	std::unique_ptr<sf::Sprite> sprite;
	std::string path = "Resources/sword.bmp";
};

#endif