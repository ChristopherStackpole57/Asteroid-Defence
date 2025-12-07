// Christopher Stackpole, 12/06/2025

#ifndef CALL_SERVICE_H
#define CALL_SERVICE_H

#include <iterator>

#include "Services/ServiceInterface.h"
#include "GameObjects/GameObjectInterface.h"

#include "CallOrder.h"

class CallService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt);

	void SetServiceStartupPriority(IService* service, int priority);
	void SetServiceTickPriority(IService* service, int priority);

	void SetObjectStartupPriority(IGameObject* game_object, int priority);
	void SetObjectTickPriority(IGameObject* game_object, int priority);
private:
	CallOrder<IService*> service_startup_order;
	CallOrder<IService*> service_tick_order;

	CallOrder<IGameObject*> object_startup_order;
	CallOrder<IGameObject*> object_tick_order;
};

#endif