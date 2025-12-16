// Christopher Stackpole, 12/12/2025

#ifndef ASTEROID_SERVICE_H
#define ASTEROID_SERVICE_H

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>

#include "Services/ServiceInterface.h"

#include "Services.h"

#include "Services/GameServices/PoolService/PoolService.h"

//#include "GameObjects/Asteroid.h"

constexpr int ASTEROID_SPAWN_CHANCE = 8000;
constexpr float ASTEROID_SPAWN_DECAY_FACTOR = 0.000005;
constexpr float ASTEROID_SPEED = 100.f;

class Asteroid;
class AsteroidService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;

	std::vector<Asteroid*> GetAsteroids();
private:
	// Using a set to enforce uniqueness, as these are asteroid references are fetched from pool service
	std::set<Asteroid*> asteroids;
};

#endif