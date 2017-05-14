#include "stdafx.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{
	vx = 0;
	vy = 0;
}

Bullet::Bullet(float x, float y, float angle, sf::Texture & tex, bool acc, Enum::Tag t)
{
	shape.setPosition(x, y);
	shape.setRotation(angle);
	shape.setTexture(tex);
	acceleration = acc;

	if(acc == false)
		shape.scale(0.5, 0.5);

	target = nullptr;
	tag = t;

	setSpeed();
	setColliderRadius(shape.getLocalBounds().height / 2);
}

Bullet::~Bullet()
{
	if (target != nullptr)
		delete target;
}

void Bullet::setSpeed()
{
	float sp = speed;
	if (acceleration == true)
		sp /= 7;

	float xN = static_cast<float>(sin(M_PI * shape.getRotation() / 180.f));
	float yN = static_cast<float>(cos(M_PI * shape.getRotation() / 180.f));

	vx = xN * sp;
	vy = -yN * sp;
}

void Bullet::accelerate(float dt)
{
	float angle = shape.getRotation();
	
	//ustaw predkosc!
	float sp = speed / 10;

	float xN = static_cast<float>(sin(M_PI * (angle / 180)));
	float yN = static_cast<float>(cos(M_PI * (angle / 180)));

	vx += xN*5.f*sp*dt;
	vy -= yN*5.f*sp*dt;

	shape.setRotation(atan2(vy, vx) * 180/M_PI + 90);
}

void Bullet::accelerateToTarget(float dt, sf::Vector2f tar)
{
	if (target == nullptr)
		target = new sf::Vector2f(tar);
	else
		*target = tar;

	//dlugosc wektora celu
	float distanceVector = sqrt(pow(tar.x - shape.getPosition().x, 2) + pow(tar.y - shape.getPosition().y, 2));
	//dlugosc wektora predkosci
	float speedMagnitude = sqrt(pow(vx, 2) + pow(vy, 2));

	//wektor wprost to do celu
	float xTarget = ((target->x - shape.getPosition().x));
	float yTarget = ((target->y - shape.getPosition().y));

	//sinus kata miedzy wektorami, bedziemy obrac w strone w ktora szybciej wykona sie obrot
	float sina = (xTarget*vy - yTarget*vx)/ (distanceVector*speedMagnitude);
	float sina2 = (vx*yTarget - vy*xTarget) / (distanceVector*speedMagnitude);

	float result = asin(sina2);
	float angle = result * (180 / M_PI);
	result /= 30;
	result = abs(result);

	if (result <= 0.001f)
	{
		vx = vx * 1.01;
		vy = vy * 1.01;
		return;
	}
		
	float calcX;
	float calcY;

	if (sina <= sina2)
	{
		calcX = vx * cos(result) - vy * sin(result);
		calcY = vx * sin(result) + vy * cos(result);
	}
	else
	{
		calcX = vx * cos(result) - vy * sin(-result);
		calcY = vx * sin(-result) + vy * cos(result);
	}

	shape.setRotation(atan2(calcY,calcX)*180/M_PI + 90);

	vx = calcX * 1.01;
	vy = calcY * 1.01;
}

void Bullet::destroy()
{
	delete this;
}

void Bullet::setPosition(float x, float y)
{
	shape.setPosition(x, y);
}

void Bullet::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
}

void Bullet::setRotation(float angle)
{
	shape.setRotation(angle);
}

void Bullet::setAcceletation(bool acc)
{
	acceleration = acc;
}

void Bullet::setTexture(sf::Texture & tex)
{
	shape.setTexture(tex);
}

sf::Vector2f Bullet::getPosition()
{
	return shape.getPosition();
}


void Bullet::update(float dt, sf::Vector2f tar)
{
	if (acceleration == true)
	{
		accelerateToTarget(dt, tar);
	}
		
	shape.move(vx*dt, vy*dt);
	Collider::setPosition(shape.getPosition());
}

void Bullet::setTag(Enum::Tag t)
{
	tag = t;
}

Enum::Tag Bullet::getTag()
{
	return tag;
}

sf::FloatRect Bullet::getBoundingBox()
{
	return shape.getGlobalBounds();
}

sf::Vector2f Bullet::getNextPosition()
{
	return sf::Vector2f(shape.getPosition().x + vx, shape.getPosition().y + vy);
}

void Bullet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape);
}