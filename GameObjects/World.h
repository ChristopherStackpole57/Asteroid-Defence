// Christopher Stackpole, 12/08/2025

#ifndef WORLD_H
#define WORLD_H

#include "Services/EngineServices/RenderService/RenderObject.h"

#include "GameObjects/GameObjectInterface.h"

class World : public IGameObject
{
public:
	void Start() override;

private:

};

#endif