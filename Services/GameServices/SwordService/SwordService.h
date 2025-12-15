// Christopher Stackpole, 12/15/2025

#ifndef SWORD_SERVICE_H
#define SWORD_SERVICE_H

#include <deque>
#include <memory>

#include "ServiceControl.h"
#include "Services.h"

#include "InputService.h"

class SWORD;
class SwordService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;
private:
	void UpdateSwordPositions();

	std::deque<std::unique_ptr<SWORD>> swords;
};

#endif