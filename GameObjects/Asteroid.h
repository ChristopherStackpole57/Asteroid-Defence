// Christopher Stackpole, 12/11/2025

#ifndef ASTEROID_H
#define ASTEROID_H

#include <cstdlib>

#include "Services.h"

#include "GameObjects/GameObjectInterface.h"

#include "GameObjects/Laser.h"
#include "GameObjects/World.h"

constexpr float ASTEROID_MAX_HEALTH = 100.f;
constexpr float ASTEROID_MIN_GEN_HEALTH = 50.f;

class Asteroid : public IGameObject
{
public:
	Asteroid();

	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;
	
	void SetPosition(sf::Vector2f position) override;
	sf::Vector2f GetPosition() override;

	sf::Vector2f GetSize() override;

	void ResetSize();
	void ResetHealth();
private:
	float health = ASTEROID_MAX_HEALTH;
	float tex_rad = 0.f;

	std::unique_ptr<sf::Sprite> sprite;
	std::string path = "Resources/asteroid.bmp";
};

#endif