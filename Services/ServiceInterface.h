// Christopher Stackpole, 12/06/2025

#ifndef ISERVICE_H
#define ISERVICE_H

#include <string>

class IService
{
public:
	virtual ~IService() = default;
	
	virtual void Start() = 0;
	virtual void Shutdown() = 0;
	virtual void Tick(float dt) {};

	std::string Name;
};

#endif