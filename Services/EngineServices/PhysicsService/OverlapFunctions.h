// Christopher Stackpole, 12/14/2025

#ifndef OVERLAP_FUNCTIONS_H
#define OVERLAP_FUNCTIONS_H

#include <algorithm>
#include <cmath>

#include "Services/EngineServices/PhysicsService/Body.h"

inline bool ResolveOverlap(Body& a, const Circle& ca, Body& b, const Circle& cb)
{
	float distsq = sf::Vector2f(a.GetPosition() - b.GetPosition()).lengthSquared();
	float rsum = ca.radius + cb.radius;
	return (distsq <= rsum * rsum);
}
inline bool ResolveOverlap(Body& a, const Circle& ca, Body& b, const Rect& rb)
{
	sf::Vector2f separation = a.GetPosition() - b.GetPosition();
	sf::Vector2f clamped = sf::Vector2f(
		std::clamp(separation.x, -rb.half_axis.x, rb.half_axis.x),
		std::clamp(separation.y, -rb.half_axis.y, rb.half_axis.y)
	);
	sf::Vector2f closest = b.GetPosition() + clamped;
	float distsq = (a.GetPosition() - closest).lengthSquared();
	return distsq <= ca.radius * ca.radius;
}
inline bool ResolveOverlap(Body& a, const Rect& ra, Body& b, const Circle& cb)
{
	return ResolveOverlap(b, cb, a, ra);
}
inline bool ResolveOverlap(Body& a, const Rect& ra, Body& b, const Rect& rb)
{
	sf::Vector2f separation = a.GetPosition() - b.GetPosition();
	return
		(std::abs(separation.x) <= ra.half_axis.x + rb.half_axis.x) &&
		(std::abs(separation.y) <= ra.half_axis.y + rb.half_axis.y);
}

#endif