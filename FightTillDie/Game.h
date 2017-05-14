#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>

class Game
{
private:
	sf::Music music;
	enum GameState {MENU,GAME,GAME_OVER,END};
	GameState state;

	sf::Font font;

	bool entry = true;
public:
	Game();
	~Game();

	void runGame();

	int single();
	void menu(int);
};

