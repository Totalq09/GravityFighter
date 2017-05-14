#pragma once
#include "stdafx.h"
#include "Tag.h"
#include "Collider.h"
#include <SFML\Graphics.hpp>

#define M_PI        3.14159265358979323846264338327950288 

class Bullet : public sf::Drawable, public sf::Transformable, public Collider
{
private:
	Enum::Tag tag;
	float vx;
	float vy;
	
	const float speed = 1000.f;
	bool acceleration;

	sf::Vector2f *target;

	sf::Sprite shape;

	void setSpeed();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Bullet();
	Bullet(float x, float y, float angle, sf::Texture & tex, bool acc, Enum::Tag t);
	~Bullet();

	void accelerate(float dt);
	void accelerateToTarget(float dt, sf::Vector2f tar);
	void destroy();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);
	void setRotation(float angle);
	void setAcceletation(bool acc = false);
	void setTag(Enum::Tag t);
	void setTexture(sf::Texture & tex);

	sf::Vector2f getPosition();

	Enum::Tag getTag();

	sf::FloatRect getBoundingBox();

	sf::Vector2f getNextPosition();

	void update(float dt, sf::Vector2f tar);
};

