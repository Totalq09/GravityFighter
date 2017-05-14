#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Explosion : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sound sound;

	const float frameTime = 35.f;
	int currentFrameX;
	int currentFrameY;

	sf::Clock timer;

	sf::IntRect currentTexture;
	sf::Sprite shape;

	int texSize;
	int texTotalSize;
	bool toDelete;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	Explosion(sf::Vector2f pos, sf::Texture &tex, sf::SoundBuffer & s);
	~Explosion();

	void update();
	bool isToDelete();
	void destroy();
};

