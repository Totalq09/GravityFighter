#pragma once
#include <SFML\Graphics.hpp>
class Collider
{
private:
	sf::CircleShape collider;
public:
	void setColliderRadius(float rad);
	float getColliderRadius();
	
	virtual void setPosition(sf::Vector2f pos);
	virtual sf::Vector2f getPosition();


	Collider(float rad);
	Collider();
	~Collider();
};

