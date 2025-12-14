// Christopher Stackpole, 12/13/2025

#ifndef BODY_H
#define BODY_H

#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Services/EngineServices/PhysicsService/Collider.h"

class IGameObject;
class Body
{
public:
	Body() : collider(Circle{ 0.f }) {};

	void SetOwner(IGameObject* owner);
	IGameObject* GetOwner();

	using ColCallback = std::function<void(Body& self, Body& other)>;
	void SetOnOverlap(ColCallback callback);
	void InvokeOverlap(Body& other);

	void SetActive(bool active);
	bool GetActive();

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();

	void SetVelocity(sf::Vector2f velocity);
	sf::Vector2f GetVelocity();

	void SetAcceleration(sf::Vector2f acceleration);
	sf::Vector2f GetAcceleration();

	void SetCollider(const Circle& collider);
	void SetCollider(const Rect& collider);
	const Collider& GetCollider();
private:
	IGameObject* owner = nullptr;
	ColCallback on_overlap;

	bool active = true;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	Collider collider;
};

#endif