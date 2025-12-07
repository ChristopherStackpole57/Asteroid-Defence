// Christopher Stackpole, 12/06/2025

#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

class IGameObject
{
public:
	virtual ~IGameObject() = default;
	
	virtual void Start() = 0;
	virtual void Shutdown() = 0;
	virtual void Tick(float dt) {};
};

#endif