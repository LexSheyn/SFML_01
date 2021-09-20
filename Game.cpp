#include "Game.h"

//Private functions
void Game::InitVariables()
{
	//Window
	this->window = nullptr;

	//Colors
	this->color =		sf::Color(255, 255, 255, 255);
	this->VeryHard =	sf::Color(255,  55,   0, 255);
	this->Hard =		sf::Color(205, 105,   0, 255);
	this->Medium =		sf::Color(155, 155,   0, 255);
	this->Easy =		sf::Color(105, 205,   0, 255);
	this->VeryEasy =	sf::Color( 55, 255,   0, 255);

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 100;
	this->enemySize = 60.f;
	this->enemySpawnTimerMax = 32.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;	
	this->maxEnemies = 12;
	this->mouseHeld = false;
}

void Game::InitWindow()
{
	this->videoMode.width = 1120;
	this->videoMode.height = 630;

	this->window = new sf::RenderWindow(this->videoMode, "Game 01", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60); //60 FPS
}

void Game::InitFonts()
{
	if (!this->font.loadFromFile("../Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts!" << "\n";
	}

	if (!this->fontHealth.loadFromFile("../Fonts/Penguin-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts!" << "\n";
	}
}

void Game::InitText()
{
	//Font ui
	this->uiText.setPosition(20.f, 20.f);
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color(205, 205, 205, 255));
	this->uiText.setOutlineColor(sf::Color(125, 125, 125, 255));
	this->uiText.setOutlineThickness(1.f);
	this->uiText.setString("NONE");

	//Font points
	this->uiTextPoints.setPosition(100.f, 20.f);
	this->uiTextPoints.setFont(this->font);
	this->uiTextPoints.setCharacterSize(24);
	this->uiTextPoints.setFillColor(sf::Color(205, 205, 205, 255));
	this->uiTextPoints.setOutlineColor(sf::Color(125, 125, 125, 255));
	this->uiTextPoints.setOutlineThickness(1.f);
	this->uiTextPoints.setString("NONE");

	//Font health
	this->uiTextHealth.setPosition(100.f, 44.f);
	this->uiTextHealth.setFont(this->fontHealth);
	this->uiTextHealth.setCharacterSize(36);
	this->uiTextHealth.setFillColor(sf::Color(205, 205, 205, 255));
	this->uiTextHealth.setOutlineColor(sf::Color(125, 125, 125, 255));
	this->uiTextHealth.setOutlineThickness(1.f);
	this->uiTextHealth.setString("NONE");
}

void Game::InitEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(this->enemySize, this->enemySize));
	//this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color(55, 205, 55, 255));
	this->enemy.setOutlineColor(sf::Color(0, 125, 0, 255));
	this->enemy.setOutlineThickness(this->enemySize/20);
}

//Constructors and Distructors
Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitFonts();
	this->InitText();
	this->InitEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
	/*
		@return void

		Spawns the enemies and sets their sizes colors.
		Spawns them at random positions.
		- Sets a random type (diff)
		- Sets a random position
		- Sets a random color
		- Adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	//Randomie enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f((this->enemySize * 2) / 6, (this->enemySize * 2) / 6));
		this->color = this->VeryHard;
		this->enemy.setFillColor(this->color);
		this->color.r -= 40;
		this->color.g -= 40;
		this->enemy.setOutlineColor(this->color);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f((this->enemySize * 3) / 6, (this->enemySize * 3) / 6));
		this->color = this->Hard;
		this->enemy.setFillColor(this->color);
		this->color.r -= 40;
		this->color.g -= 40;
		this->enemy.setOutlineColor(this->color);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f((this->enemySize * 4) / 6, (this->enemySize * 4) / 6));
		this->color = this->Medium;
		this->enemy.setFillColor(this->color);
		this->color.r -= 40;
		this->color.g -= 40;
		this->enemy.setOutlineColor(this->color);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f((this->enemySize * 5) / 6, (this->enemySize * 5) / 6));
		this->color = this->Easy;
		this->enemy.setFillColor(this->color);
		this->color.r -= 40;
		this->color.g -= 40;
		this->enemy.setOutlineColor(this->color);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(this->enemySize, this->enemySize));
		this->color = this->VeryEasy;
		this->enemy.setFillColor(this->color);
		this->color.r -= 40;
		this->color.g -= 40;
		this->enemy.setOutlineColor(this->color);
		break;
	default:
		break;
	}

	//this->enemy.setFillColor(sf::Color(255, 55, 55, 255));
	//this->enemy.setOutlineColor(sf::Color(255, 0, 0, 155));
	//this->enemy.setOutlineThickness(6.f);

	//Spawm the enemy
	this->enemies.push_back(this->enemy);

	//Remove enemies at end of the screen
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		@return void

		Updates the mouse positions
		- Mouse positions relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;
	std::stringstream ssPoints;
	std::stringstream ssHealth;

	ss << "Points:\n"
	   << "Health:\n";

	ssPoints << this->points << "\n";

	ssHealth << this->health << "\n";

	this->uiText.setString(ss.str());
	this->uiTextPoints.setString(ssPoints.str());
	this->uiTextHealth.setString(ssHealth.str());
}

void Game::updateEnemies()
{
	/*
		@return void

		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than maximum.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen. //TODO
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	//Moving and updating enemies
	//for (auto& e : this->enemies)
	for (int i = 0; i < this->enemies.size(); i++)
	{		
		//e.move(0.f, 1.f);
		bool deleted = false;

		if (this->enemies[i].getFillColor() == this->VeryHard)
		{
			this->enemies[i].move(0.f, 1.f);
		}
		else if (this->enemies[i].getFillColor() == this->Hard)
		{
			this->enemies[i].move(0.f, 2.f);
		}
		else if (this->enemies[i].getFillColor() == this->Medium)
		{
			this->enemies[i].move(0.f, 3.f);
		}
		else if (this->enemies[i].getFillColor() == this->Easy)
		{
			this->enemies[i].move(0.f, 4.f);
		}
		else if (this->enemies[i].getFillColor() == this->VeryEasy)
		{
			this->enemies[i].move(0.f, 5.f);
		}
		
		//If the enemy is past the bottom of the screen, delete them
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

			if (this->enemies[i].getFillColor() == this->VeryHard)
			{
				this->health -= 10;
			}
			else if (this->enemies[i].getFillColor() == this->Hard)
			{
				this->health -= 8;
			}
			else if (this->enemies[i].getFillColor() == this->Medium)
			{
				this->health -= 6;
			}
			else if (this->enemies[i].getFillColor() == this->Easy)
			{
				this->health -= 4;
			}
			else if (this->enemies[i].getFillColor() == this->VeryEasy)
			{
				this->health -= 2;
			}
						
			std::cout << "Health: " << this->health << "\n";
		}
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;

			bool deleted = false;

			for (size_t i = 0; i < enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if (this->enemies[i].getFillColor() == this->VeryHard)
					{
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == this->Hard)
					{
						this->points += 8;
					}
					else if (this->enemies[i].getFillColor() == this->Medium)
					{
						this->points += 6;
					}
					else if (this->enemies[i].getFillColor() == this->Easy)
					{
						this->points += 4;
					}
					else if (this->enemies[i].getFillColor() == this->VeryEasy)
					{
						this->points += 2;
					}
					std::cout << "Points: " << this->points << "\n";

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	//End game condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->uiTextPoints);
	target.draw(this->uiTextHealth);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	/*
		@return	void

		- clear old frame
		- render objects
		- display frame in a window

		Renders the Game objects
	*/

	this->window->clear(sf::Color(0, 0, 0, 255));

	//Draw Game object
	this->renderText(*this->window);

	this->renderEnemies(*this->window);

	this->window->display();
}






















