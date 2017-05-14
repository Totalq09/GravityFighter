#include "stdafx.h"
#include "Engine.h"
#include <iostream>

//////////////////////////////////////////////////////////

Engine::Engine(sf::RenderWindow &win, sf::View &vi)
{
	if (!font.loadFromFile("Mecha.ttf"))
	{
		exit(111);
	}

	if (!buffer.loadFromFile("explosion_sound.wav"))
	{
		exit(222);
	}

	window = &win;
	view = &vi;

	view->setCenter(window->getSize().x / 2, window->getSize().y / 2);
	view->setSize(window->getSize().x, window->getSize().y);

	///////////TEXTURE LOADING///////////////

	if (!background_t.loadFromFile("milky.jpg"))
	{
		exit(10);
	};

	if (!planet_tex.loadFromFile("earth.jpg"))
	{
		exit(10);
	}
	
	if(!bullet_tex.loadFromFile("missile.png"))
	{
		exit(10);
	}

	if (!explosion_tex.loadFromFile("explosion.png"))
	{
		exit(10);
	}

	background.setTexture(background_t);

	zoom_count = 0;

	planets.push_back(new Planet);
	planets[0]->setTexture(planet_tex);
	planets[0]->setRadius(100);
	planets[0]->setPosition(sf::Vector2f(375, 375));
	planets[0]->setMass(23000);

	planets.push_back(new Planet);
	planets[1]->setTexture(planet_tex);
	planets[1]->setRadius(100);
	planets[1]->setPosition(sf::Vector2f(window->getSize().x -375, window->getSize().y -375));
	planets[1]->setMass(32000);

	planets.push_back(new Planet);
	planets[2]->setTexture(planet_tex);
	planets[2]->setRadius(170);
	planets[2]->setPosition(sf::Vector2f(window->getSize().x /2, window->getSize().y /2));
	planets[2]->setMass(6000);

	player2.setPosition(window->getSize().x-100, window->getSize().y-900);
	player2.setColor(sf::Color::Magenta);
	player2.rotate(180);
}

Engine::~Engine()
{
	for (auto it = planets.begin(); it < planets.end(); it++)
	{
		delete *it;
	}
	planets.clear();

	for (std::vector<Bullet *>::iterator i = bullets.begin(); i < bullets.end(); i++)
	{
		delete *i;
	}
	bullets.clear();

	for (auto it = explosions.begin(); it < explosions.end(); it++)
	{
		delete *it;
	}
	explosions.clear();
}

int Engine::runEngine()
{
	bool end = false;

	window->setFramerateLimit(60.0f);
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (!end)
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			sf::Event event;
			sf::Vector2f mouse(sf::Mouse::getPosition());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player.rotate(-4);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player.rotate(4);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player.accelerate(TimePerFrame.asSeconds());
				/*if (zoom_count < 200)
				{
					view->zoom(0.9998);
					zoom_count++;
				}*/
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player2.rotate(-4);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player2.rotate(4);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player2.accelerate(TimePerFrame.asSeconds());
			}

			//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			//{
			//	/*if (zoom_count > 0)
			//	{
			//		view->zoom(1.0002);
			//		zoom_count--;
			//	}*/
			//}

			if (!roundEnd)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && player.isShooted() == false)
				{
					bullets.push_back(new Bullet(player.getPosition().x, player.getPosition().y, player.getRotation(), bullet_tex, false, Enum::Tag::Player));
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && player.isShootedAlternative() == false)
				{
					bullets.push_back(new Bullet(player.getPosition().x, player.getPosition().y, player.getRotation(), bullet_tex, true, Enum::Tag::Player));
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && player2.isShooted() == false)
				{
					bullets.push_back(new Bullet(player2.getPosition().x, player2.getPosition().y, player2.getRotation(), bullet_tex, false, Enum::Tag::Enemy));
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && player2.isShootedAlternative() == false)
				{
					bullets.push_back(new Bullet(player2.getPosition().x, player2.getPosition().y, player2.getRotation(), bullet_tex, true, Enum::Tag::Enemy));
				}
			}
			
			while (window->pollEvent(event))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					end = true;
				}
			}

			update(TimePerFrame.asSeconds());
		}
		
		draw();

		if (roundEnd == true)
		{
			std::cout << clockEnd.getElapsedTime().asSeconds() << std::endl;
			if (clockEnd.getElapsedTime().asSeconds() > 1.5f)
			{
				
				end = true;
			}
		}
	}

	if (player.isAlive())
		return 0;
	else
		return 1;
}

void Engine::reset()
{
	for (std::vector<Bullet *>::iterator i = bullets.begin(); i < bullets.end(); i++)
	{
		delete *i;
	}
	bullets.clear();

	for (auto it = explosions.begin(); it < explosions.end(); it++)
	{
		delete *it;
	}
	explosions.clear();

	player.setPosition(100, 900);
	player2.setPosition(window->getSize().x - 100, window->getSize().y - 900);
	player2.setColor(sf::Color::Magenta);

	player.setLife(100);
	player2.setLife(100);

	roundEnd = false;
}

void Engine::update(float dt)
{
	addGravitionalAcceleration(dt, &player);
	addGravitionalAcceleration(dt, &player2);

	if (player.isAlive())
	{
		player.update(dt);
		flame1.update(player.getPosition(), player.getRotation());
	}
	if (player2.isAlive())
	{
		player2.update(dt);
		flame2.update(player2.getPosition(), player2.getRotation());
	}
	
	for (auto it = bullets.begin(); it != bullets.end(); it++)
	{
		if((*it)->getTag() == Enum::Tag::Player)
			(*it)->update(dt, player2.getPosition());
		else
			(*it)->update(dt, player.getPosition());
	}

	for (auto it = explosions.begin(); it != explosions.end(); )
	{
		(*it)->update();

		if ((*it)->isToDelete() == true)
		{
			(**it).destroy();
			it = explosions.erase(it);
			continue;
		}
		it++;
	}

	if (roundEnd == false)
	{
		checkIsInBounds();
		collision();
	}

	for (int i = 0; i<2; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(45);
		
		if (i == 0)
		{
			std::stringstream ss;
			ss << player.getLife();
			text[i].setString("Green life: " + ss.str());
			text[i].setPosition(5, 5);		
		}
			
		else
		{
			std::stringstream ss;
			ss << player2.getLife();
			text[i].setString("Purple life: " + ss.str());
			text[i].setPosition(window->getSize().x - text[i].getGlobalBounds().width - 5, 5);
		}
	}
}

void Engine::draw()
{
	window->clear();
	window->setView(*view);
	window->draw(background);

	window->draw(text[0]);
	window->draw(text[1]);

	if (player.isAlive())
	{
		window->draw(flame1);
		window->draw(player);
	}

	if (player2.isAlive())
	{
		window->draw(player2);
		window->draw(flame2);
	}

	for(auto it = planets.begin(); it != planets.end(); it++)
		window->draw(**it);

	for (auto it = bullets.begin(); it != bullets.end(); it++)
		window->draw(**it);

	for (auto it = explosions.begin(); it != explosions.end(); it++)
		window->draw(**it);

	window->display();
}

///////////////////////////////////////////////////

void Engine::addGravitionalAcceleration(float dt, Player * player)
{
	float distance_2;

	for (int i = 0; i < number_of_planet; i++)
	{
		distance_2 = pow((planets[i]->getPosition().x - player->getPosition().x), 2) + pow((planets[i]->getPosition().y - player->getPosition().y), 2);

		if (distance_2 < 10) return;

		float power = (planets[i]->getMass() / (distance_2));

		player->accelerate(dt, power, planets[i]->getPosition(), sqrt(distance_2));
	}
}

void Engine::checkIsInBounds()
{
	if (player.getPosition().x < -20 || player.getPosition().x > window->getSize().x + 20 ||
		player.getPosition().y < -20 || player.getPosition().y > window->getSize().y + 20)
	{
		clockEnd.restart();
		roundEnd = true;
		player.decreaseLife(100);
	}
	if (player2.getPosition().x < -20 || player2.getPosition().x > window->getSize().x + 20 ||
		player2.getPosition().y < -20 || player2.getPosition().y > window->getSize().y + 20)
	{
		clockEnd.restart();
		roundEnd = true;
		player2.decreaseLife(100);
	}

	for (auto it = bullets.begin(); it != bullets.end();)
	{
		if ((**it).getPosition().x < -20 || (**it).getPosition().x > window->getSize().x + 20 ||
			(**it).getPosition().y < -20 || (**it).getPosition().y > window->getSize().y + 20)
		{
			(**it).destroy();
			it = bullets.erase(it);
		}
		else
		{
			it++;
		}
	}
}

////////////////////////////////////////////

void Engine::collision()
{
	//collisions with planets
	for (auto itPlanets = planets.begin(); itPlanets != planets.end(); itPlanets++)
	{
		for (auto itBullets = bullets.begin(); itBullets != bullets.end();)
		{
			if (checkCollision(*itPlanets, *itBullets) == true)
			{
				explosions.push_back(new Explosion((**itBullets).getPosition(), explosion_tex, buffer));
				(**itBullets).destroy();
				itBullets = bullets.erase(itBullets);	
			}
			else
				itBullets++;
		}

		if (checkCollision(*itPlanets, &player) == true)
		{
			explosions.push_back(new Explosion(player.getPosition(), explosion_tex, buffer));
			clockEnd.restart();
			roundEnd = true;
			player.decreaseLife(100);
		}

		if (checkCollision(*itPlanets, &player2) == true)
		{
			explosions.push_back(new Explosion(player2.getPosition(), explosion_tex, buffer));
			clockEnd.restart();
			roundEnd = true;
			player2.decreaseLife(100);
		}
	}

	//bullets with players
	{
		for (auto itBullets = bullets.begin(); itBullets != bullets.end();)
		{
			if ((**itBullets).getTag() == Enum::Tag::Enemy)
			{
				if (checkCollision(&player, *itBullets) == true)
				{
					player.decreaseLife(25);
					explosions.push_back(new Explosion(player.getPosition(), explosion_tex, buffer));
					(**itBullets).destroy();
					itBullets = bullets.erase(itBullets);
				}
				else
					itBullets++;
			}
			else
			{
				if (checkCollision(&player2, *itBullets) == true)
				{
					player2.decreaseLife(25);
					explosions.push_back(new Explosion(player2.getPosition(), explosion_tex, buffer));
					(**itBullets).destroy();
					itBullets = bullets.erase(itBullets);
				}
				else
					itBullets++;
			}
		}
	}

	if (player.isAlive() == false || player2.isAlive() == false)
	{
		clockEnd.restart();
		roundEnd = true;
	}
		
}

bool Engine::checkCollision(Collider* obj1, Collider* obj2)
{
	float distance = sqrt(pow((*obj1).getPosition().x - (*obj2).getPosition().x, 2) + pow((*obj1).getPosition().y - (*obj2).getPosition().y, 2));

	if (distance <= (*obj1).getColliderRadius()+(*obj2).getColliderRadius())
	{
		return true;
	}
	else
		return false;
}
