#pragma once
#include "stdafx.h"
#include "Collider.h"
#include <SFML\Graphics.hpp>
#include "Flame.h"

#define M_PI        3.14159265358979323846264338327950288 

class Player : public sf::Drawable, public sf::Transformable, public Collider
{
private:
	sf::ConvexShape shape;
	
	int life = 100;

	float speed;
	//unsigned static const int max_speed = 75;

	float vx;
	float vy;

	sf::Clock clockIsShooted;
	sf::Clock clockIsShootedAlternative;
	const float shootingTime = 150;
	const float shootingAlternativeTime = 2000;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Player();
	~Player();

	void setColor(sf::Color c);

	sf::FloatRect getBoundingBox();

	bool isShooted();
	bool isShootedAlternative();

	void setLife(int l);
	int getLife();
	bool decreaseLife(int amount);
	bool isAlive();

	sf::Vector2f getPosition(size_t index);
	sf::Vector2f getPosition();
	
	void update(float TimePerFrame);
	void playAnimation(bool play);

	void setPosition(float x, float y);
	void rotate(int angle);
	void scale(float a, float b);

	void accelerate(float dt, float power, sf::Vector2f target, float distance);
	void accelerate(float dt);

	void setVelocity(int x, int y);
	float getRotation();

	sf::Vector2f getVelocity();
	sf::Vector2f getNextPosition();
};

