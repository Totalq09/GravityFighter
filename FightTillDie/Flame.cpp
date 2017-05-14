#include "stdafx.h"
#include "Flame.h"

void Flame::setTexture(sf::Texture &tex)
{
	shape.setTexture(tex);
}

void Flame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape);
}

void Flame::update(sf::Vector2f pos, float angle)
{
	setPosition(pos, angle);

	if (timer.getElapsedTime().asMilliseconds() > frameTime)
	{
		currentFrameX++;
		if (currentFrameX > 3)
			currentFrameX = 0;

		currentTexture = sf::IntRect(currentFrameX*texSize, 0, texSize, texSize);

		shape.setTextureRect(currentTexture);

		timer.restart();
	}
}

void Flame::setPosition(sf::Vector2f pos, float angle)
{
	shape.setPosition(pos);
	shape.setRotation(angle);
}


Flame::Flame()
{
	if (!tex.loadFromFile("flames.png"))
	{
		exit(102);
	}
	texSize = 128;
	currentFrameX = 0;
	timer.restart();
	currentTexture = sf::IntRect(0, 0, texSize, texSize);
	shape.setTexture(tex);
	shape.setScale(0.75, 0.75);
	shape.setOrigin(texSize / 2, texSize / 2);
	shape.setTextureRect(currentTexture);
}

Flame::~Flame()
{
}
