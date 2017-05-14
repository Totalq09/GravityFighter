#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player()
{
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(30, 40));
	shape.setPoint(1, sf::Vector2f(40, 60));
	shape.setPoint(2, sf::Vector2f(30, 30));
	shape.setPoint(3, sf::Vector2f(20, 60));

	shape.setFillColor(sf::Color::Green);

	shape.setOrigin(30, 40);
	shape.setPosition(100, 900);
	speed = 1400;

	vx = vy = 0;

	clockIsShooted.restart();
	clockIsShootedAlternative.restart();
	setColliderRadius(10);
}

Player::~Player()
{
}

void Player::setColor(sf::Color c)
{
	shape.setFillColor(c);
}

sf::FloatRect Player::getBoundingBox()
{
	return shape.getGlobalBounds();
}

bool Player::isShooted()
{
	if (clockIsShooted.getElapsedTime().asMilliseconds() > shootingTime)
	{
		clockIsShooted.restart();
		return false;
	}

	return true;
}

bool Player::isShootedAlternative()
{
	if (clockIsShootedAlternative.getElapsedTime().asMilliseconds() > shootingAlternativeTime)
	{
		clockIsShootedAlternative.restart();
		return false;
	}

	return true;
}

void Player::setLife(int l)
{
	life = l;
}

int Player::getLife()
{
	return life;
}

bool Player::decreaseLife(int amount)
{
	life -= amount;
	return isAlive();
}

bool Player::isAlive()
{
	if (life > 0)
		return true;
	else
		return false;
}


sf::Vector2f Player::getPosition(size_t index)
{
	return shape.getPoint(index);
}


sf::Vector2f Player::getPosition()
{
	return shape.getPosition();
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape);
}

void Player::update(float dt)
{
	shape.move(vx*dt, vy*dt);
	Collider::setPosition(shape.getPosition());
}

void Player::playAnimation(bool play)
{

}

void Player::setPosition(float x, float y)
{
	shape.setPosition(x, y);
}

void Player::accelerate(float dt, float power, sf::Vector2f target, float distance)
{
	float xN = ((target.x - shape.getPosition().x));
	float yN = ((target.y - shape.getPosition().y));

	    vx += xN * power * dt;
		vy += yN * power * dt;
}

void Player::accelerate(float dt)
{
	float angle = shape.getRotation();

	float xN = static_cast<float>(sin( M_PI * (angle / 180)));
	float yN = static_cast<float>(cos( M_PI * (angle / 180)));

	vx += xN * 0.2f*speed*dt;
	vy -= yN * 0.2f*speed*dt;
}

void Player::rotate(int angle)
{
	shape.rotate(angle);
}

void Player::scale(float a, float b)
{
	shape.scale(a, b);
}


void Player::setVelocity(int x, int y)
{
	vx = x;
	vy = y;
}

sf::Vector2f Player::getVelocity()
{
	return sf::Vector2f(vx, vy);
}

float Player::getRotation()
{
	return shape.getRotation();
}

sf::Vector2f Player::getNextPosition()
{
	return sf::Vector2f(shape.getPosition().x + vx, shape.getPosition().y + vy);
}



