// Christopher Stackpole, 12/06/2025

#ifndef INPUT_SERVICE_H
#define INPUT_SERVICE_H

#include "Services/ServiceInterface.h"

class InputService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;
private:
};

#endif