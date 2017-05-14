#include "stdafx.h"
#include "Explosion.h"
#include <iostream>


Explosion::Explosion(sf::Vector2f pos, sf::Texture &tex, sf::SoundBuffer &s)
{
	toDelete = false;
	texTotalSize = tex.getSize().y;
	texSize = 64;
	shape.setPosition(pos);
	currentFrameX = 0;
	currentFrameY = 0;
	timer.restart();
	currentTexture = sf::IntRect(0, 0, texSize, texSize);
	shape.setTexture(tex);
	shape.setOrigin(texSize / 2, texSize / 2);
	shape.setTextureRect(currentTexture);
	sound.setBuffer(s);
	sound.play();
}

void Explosion::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape);
}

void Explosion::update()
{
	if (toDelete == true)
		return;

	if (timer.getElapsedTime().asMilliseconds() > frameTime)
	{
		std::cout << timer.getElapsedTime().asMilliseconds() << " " << frameTime << std::endl;
		currentFrameX++;
		if (currentFrameX > 3)
		{
			currentFrameX = 0;
			currentFrameY++;
		}
	
		if (currentFrameY*texSize > texTotalSize)
		{
			toDelete = true;
			return;
		}

		currentTexture = sf::IntRect(currentFrameX*texSize, currentFrameY*texSize, texSize, texSize);
		
		shape.setTextureRect(currentTexture);

		timer.restart();
	}
}

bool Explosion::isToDelete()
{
	return toDelete;
}

void Explosion::destroy()
{
	delete this;
}

Explosion::~Explosion()
{
}


