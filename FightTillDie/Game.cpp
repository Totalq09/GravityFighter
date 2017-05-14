#include "stdafx.h"
#include "Game.h"
#include "Engine.h"

sf::RenderWindow window;
sf::View view;

Game::Game()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	state = MENU;

	if (!font.loadFromFile("Mecha.ttf"))
	{
		exit(111);
	}

	window.create(sf::VideoMode(1920, 1080), "Gravity Fighter", sf::Style::Fullscreen, settings);

	if (!music.openFromFile("SOSE.ogg"))
		exit(9); // error
	music.play();
	/*view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	view.setSize(1920, 1080);*/
}


Game::~Game()
{
}

void Game::runGame()
{
	int player = 0;
	while (state != END)
	{
		switch (state)
		{
			case GameState::MENU:
				menu(player);
				break;
			case GameState::GAME:
				entry = false;
				player = single();
				state = GameState::MENU;
				break;
		}
	}
}

int Game::single()
{
	Engine engine(window, view);
	return engine.runEngine();
}

void Game::menu(int player)
{
	sf::Clock clock;
	sf::Text title("Gravity Fighter", font, 80);
	title.setStyle(sf::Text::Bold);
	title.setPosition(1920 / 2 - title.getGlobalBounds().width / 2, 20);

	const int ile = 3;

	sf::Text tekst[ile];

	std::string str[] = {"Player ", "Play","Exit"};
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);

		if (i == 0 && player == 0)
			tekst[i].setString("Green player won");
		else if (i == 0 && player == 1)
			tekst[i].setString("Purple player won");

		if(i == 1 && !entry)
			tekst[i].setString("Auto Play In 3s");

		tekst[i].setPosition(1920 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	int active = 1;

	if (entry == false)
		active = 2;

	tekst[active].setFillColor(sf::Color::Cyan);

	clock.restart();
	while (state == MENU)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//Wci?ni?cie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
				state = END;

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Down && active == 1)
				{
					tekst[active].setFillColor(sf::Color::White);
					active++;
				}

				else if (event.key.code == sf::Keyboard::Up && active == 2 && entry == true)
				{
					tekst[active].setFillColor(sf::Color::White);
					active--;
				}
			}

			tekst[active].setFillColor(sf::Color::Cyan);

			//klikni?cie EXIT
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && active == 2)
			{
				state = END;
			}
			//start gry
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && active == 1)
			{
				state = GAME;
			}
		}

	

		if (entry == false)
		{
			std::stringstream ss;
			ss << int(4.f - clock.getElapsedTime().asSeconds());
			tekst[1].setString("Auto Play In " + ss.str() + "s");

			if (clock.getElapsedTime().asSeconds() >= 3)
			{
				state = GAME;
				break;
			}
		}
		
		window.clear();

		window.draw(title);
		for (int i = 0; i < ile; i++)
		{
			if (i == 0 && entry)
				continue;
			window.draw(tekst[i]);
		}
			
		window.display();
	}
}
