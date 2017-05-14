#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

class Planet : public sf::Drawable, public sf::Transformable, public Collider
{
private:
	sf::CircleShape planet_view;
	float mass;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Planet(sf::Texture & tex, float rad);
	Planet();
	~Planet();

	void setTexture(sf::Texture & tex);
	void setColor(sf::Color col);
	void setRadius(float rad);
	void setMass(float m);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	float getMass();
	float getRadius();
};

