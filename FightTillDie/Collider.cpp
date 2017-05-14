#include "stdafx.h"
#include "Collider.h"


void Collider::setColliderRadius(float rad)
{
	collider.setRadius(rad);
}

float Collider::getColliderRadius()
{
	return collider.getRadius();
}

void Collider::setPosition(sf::Vector2f pos)
{
	collider.setPosition(pos);
}

sf::Vector2f Collider::getPosition()
{
	return collider.getPosition();
}

Collider::Collider(float rad)
{
	collider.setRadius(rad);
}

Collider::Collider()
{
}

Collider::~Collider()
{
}
