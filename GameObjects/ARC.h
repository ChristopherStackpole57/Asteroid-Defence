// Christopher Stackpole, 12/09/2025

#ifndef ARC_H
#define ARC_H

#include "Services/EngineServices/RenderService/RenderObject.h"

#include "GameObjects/GameObjectInterface.h"

class ARC : public IGameObject
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;

public:

};

#endif