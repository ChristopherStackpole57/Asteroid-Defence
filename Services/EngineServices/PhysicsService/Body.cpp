// Christopher Stackpole, 12/13/2025

#include "Body.h"

void Body::SetOwner(IGameObject* owner)
{
	this->owner = owner;
}
IGameObject* Body::GetOwner()
{
	return owner;
}

void Body::SetOnOverlap(ColCallback callback)
{
	on_overlap = std::move(callback);
}
void Body::InvokeOverlap(Body& other)
{
	if (on_overlap)
	{
		on_overlap(*this, other);
	}
}

void Body::SetActive(bool active)
{
	this->active = active;
}
bool Body::GetActive()
{
	return active;
}

void Body::SetPosition(sf::Vector2f position)
{
	this->position = position;
}
sf::Vector2f Body::GetPosition()
{
	return position;
}
void Body::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}
sf::Vector2f Body::GetVelocity()
{
	return velocity;
}
void Body::SetAcceleration(sf::Vector2f acceleration)
{
	this->acceleration = acceleration;
}
sf::Vector2f Body::GetAcceleration()
{
	return acceleration;
}

void Body::SetCollider(const Circle& collider)
{
	this->collider = collider;
}
void Body::SetCollider(const Rect& collider)
{
	this->collider = collider;
}
const Collider& Body::GetCollider()
{
	return collider;
}