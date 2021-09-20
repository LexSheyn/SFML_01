#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts like a game engine.
	Wrapper class.
*/

class Game
{
private:

	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resoueces
	sf::Font font;
	sf::Font fontPoints;
	sf::Font fontHealth;

	//Text
	sf::Text uiText;
	sf::Text uiTextPoints;
	sf::Text uiTextHealth;

	//Colors
	sf::Color color;
	sf::Color VeryHard;
	sf::Color Hard;
	sf::Color Medium;
	sf::Color Easy;
	sf::Color VeryEasy;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySize;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void InitVariables();
	void InitWindow();
	void InitFonts();
	void InitText();
	void InitEnemies();

public:

	//Constructors and Distructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;


	//Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};