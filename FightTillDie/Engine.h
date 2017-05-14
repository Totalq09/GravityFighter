#pragma once
#include <SFML/Audio.hpp>

#include "stdafx.h"
#include "Planet.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"

#include <vector>
#include <sstream>
#include <string>

class Engine
{
public:
	Engine(sf::RenderWindow &win, sf::View &vi);
	~Engine();

	int runEngine();

private:
	sf::SoundBuffer buffer;

	sf::Font font;
	sf::Text text[2];
	const float FPS = 60.0f;
	const int number_of_planet = 3;

	bool roundEnd = false;
	sf::Clock clockEnd;

	sf::RenderWindow *window;
	sf::View *view;

	Player player;
	Player player2;
	Flame flame1;
	Flame flame2;

	std::vector<Planet*> planets;
	std::vector<Bullet *> bullets;
	std::vector<Explosion *> explosions;

	//////////////////////////////////////////////////

	void update(float dt);
	void draw();
	void collision();
	void reset();

	bool checkCollision(Collider* obj1, Collider* obj2);

	void addGravitionalAcceleration(float dt, Player * player);
	void checkIsInBounds();

	sf::Texture planet_tex;
	sf::Texture background_t;
	sf::Texture bullet_tex;
	sf::Texture explosion_tex;

	sf::Sprite background;

	long zoom_count;
};

