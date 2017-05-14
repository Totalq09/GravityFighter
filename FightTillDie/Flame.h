#pragma once
#include <SFML\Graphics.hpp>

class Flame : public sf::Drawable, public sf::Transformable
{
	private:
		const float frameTime = 35.f;
		int currentFrameX;

		sf::Clock timer;

		sf::IntRect currentTexture;
		sf::Sprite shape;

		int texSize;

		sf::Texture tex;

		void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	public:
		void setTexture(sf::Texture & tex);
		Flame();
		~Flame();
		void update(sf::Vector2f pos, float angle);
		void setPosition(sf::Vector2f pos, float angle);
	};

