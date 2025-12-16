// Christopher Stackpole, 12/15/2025

#ifndef SWORD_SERVICE_H
#define SWORD_SERVICE_H

#include <memory>
#include <set>
#include <vector>

#include "ServiceControl.h"
#include "Services.h"

constexpr float SWORD_COST = 10.f;

class SWORD;
class SwordService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;

	void UpdateSwordPositions();
	void AddOreAmount(float amount);
private:
	float ore = 0.f;
	std::set<SWORD*> swords;
};

#endif