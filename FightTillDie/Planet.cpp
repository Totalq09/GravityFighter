#include "stdafx.h"
#include "Planet.h"

Planet::Planet(sf::Texture & tex, float rad)
{
	planet_view.setTexture(&tex);

	planet_view.setRadius(rad);
	planet_view.setOrigin(planet_view.getRadius(), planet_view.getRadius());
	planet_view.setPosition(0, 0);
	setColliderRadius(planet_view.getRadius());
	Collider::setPosition(planet_view.getPosition());
}

Planet::Planet()
{
}

Planet::~Planet()
{
}

void Planet::setTexture(sf::Texture & tex)
{
	planet_view.setTexture(&tex);
}

void Planet::setColor(sf::Color col)
{
	planet_view.setFillColor(col);
}

void Planet::setRadius(float rad)
{
	planet_view.setRadius(rad);
	planet_view.setOrigin(planet_view.getRadius(), planet_view.getRadius());
	setColliderRadius(planet_view.getRadius());
}

void Planet::setMass(float m)
{
	mass = m;
}

void Planet::setPosition(sf::Vector2f pos)
{
	planet_view.setPosition(pos);
	Collider::setPosition(planet_view.getPosition());
}

sf::Vector2f Planet::getPosition()
{
	return planet_view.getPosition();
}

float Planet::getMass()
{
	return mass;
}

float Planet::getRadius()
{
	return planet_view.getRadius();
}

void Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(planet_view);
}