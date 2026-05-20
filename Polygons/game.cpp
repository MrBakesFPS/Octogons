/* ===================================================================================================================
@Author:		Tyson Koopman-Baker
@Date:			5/16/2025
@File:			game.cpp
@Version:		2.0
@IDE:			Microsoft Visual Studios 2022 - Community
@Description:	This program covers all of the implementations for the Game Class from the "game.h" header file
=================================================================================================================== */

// Libraries and other include files
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "game.h"
#include "spaceObject.h"
#include "constants.h"
#include "gameOverlay.h"

// Default Game Constructor
Game::Game()
{
	gameScreen.create(
		sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
		"Octogons!",
		sf::Style::Titlebar | sf::Style::Close
	);
	gameScreen.setFramerateLimit(60);

	screenState = TITLE_SCREEN;

	mothership = nullptr;

	for (int i = 0; i < MAX_LIVES; i++) {
		lifeShips[i] = nullptr;
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		asteroids[i] = nullptr;
	}

	compareAsteroid = new SpaceObject{ ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 0, 0 };

	for (int i = 0; i < MAX_PHOTONS; i++) {
		photons[i] = nullptr;
	}

	objRandomLocation = { 0, 0 };

	objRandomVelocity = { 0, 0 };

	gameOverlay = new GameOverlay;

	copyMothership = nullptr;

	for (int i = 0; i < MAX_LIVES; i++) {
		copyLifeships[i] = nullptr;
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		copyAsteroids[i] = nullptr;
	}

	for (int i = 0; i < MAX_PHOTONS; i++) {
		copyPhotons[i] = nullptr;
	}
}

// Default Game Destructor
Game::~Game()
{
	if (mothership != nullptr)
		delete mothership;

	for (int i = 0; i < MAX_LIVES; i++) {
		if (lifeShips[i] != nullptr)
			lifeShips[i] = nullptr;
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr)
			asteroids[i] = nullptr;
	}

	if (compareAsteroid != nullptr)
		delete compareAsteroid;

	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (photons[i] != nullptr)
			delete photons[i];
	}

	if (gameOverlay != nullptr)
		delete gameOverlay;

	if (copyMothership != nullptr)
		delete copyMothership;

	for (int i = 0; i < MAX_LIVES; i++) {
		if (copyLifeships[i] != nullptr)
			copyLifeships[i] = nullptr;
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (copyAsteroids[i] != nullptr)
			copyAsteroids[i] = nullptr;
	}

	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (copyPhotons[i] != nullptr)
			delete copyPhotons[i];
	}
}

// playGame function
void Game::playGame()
{
	// Seeds the random number generator used throughout the game
	srand(time(NULL));

	while (screenState != EXIT_SCREEN) {
		if (screenState == TITLE_SCREEN)
			processTitleScreen();
		else if (screenState == GAME_SCREEN)
			processGameScreen();
		else if (screenState == GAME_OVER)
			processOverScreen();
		else if (screenState == LIVES_SCREEN)
			processLivesScreen();

	}
	gameScreen.close();
}

// initializeTitleScreen function
void Game::initializeTitleScreen()
{
	// Sets/Resets the life total its original state
	gameOverlay->changeFirstLifeLost(false);
	gameOverlay->changeLifeTotal(3);

	// Sets.Resets the game in progress to false
	gameOverlay->changeInProgress(false);

	// Creates a new ship for the title screen animation
	if (mothership != nullptr) {
		delete mothership;
		mothership = nullptr;
	}
	mothership = new SpaceObject{ SHIP, 5, getRandomLocation(), getRandomVelocity(), 0, 0 };

	// Creates 15 asteroids at different sizes for the title screen animation
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr) {
			delete asteroids[i];
			asteroids[i] = nullptr;
		}
	}
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (i >= 0 && i < 5)
			asteroids[i] = new SpaceObject{ ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 0, 0 };
		else if (i >= 5 && i < 10)
			asteroids[i] = new SpaceObject{ ASTEROID, 10, getRandomLocation(), getRandomVelocity(), 0, 0 };
		else if (i >= 10 && i < 15)
			asteroids[i] = new SpaceObject{ ASTEROID, 5, getRandomLocation(), getRandomVelocity(), 0, 0 };
	}
}

// processTitleScreen function
void Game::processTitleScreen()
{
	// Initializes the title screen
	gameOverlay->changeOverlay(TITLE_OVERLAY);
	initializeTitleScreen();

	// While the title screen is open
	while (gameScreen.isOpen() && screenState == TITLE_SCREEN) {
		// For the user input events that happen on the title screen
		sf::Event event;
		while (gameScreen.isOpen() && gameScreen.pollEvent(event)) {
			if (event.type == sf::Event::Closed) 
				screenState = EXIT_SCREEN;
 			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && gameOverlay->pauseScreenIsOpen() == false) 
				this->screenState = GAME_SCREEN;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				if (gameOverlay->pauseScreenIsOpen())
					closePauseScreen();
				else
					openPauseScreen();
			}
		}

		// Creates a rotating ship and rotating asteroids on the title screen
		mothership->changeAngle(3);
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr)
				asteroids[i]->changeAngle(1);
		}

		// Updates game objects
		mothership->updatePosition();

		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr)
				asteroids[i]->updatePosition();
		}

		// Draws new frame
		gameScreen.clear();
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr) {
				asteroids[i]->draw(gameScreen);
			}
		}
		mothership->draw(gameScreen);
		gameOverlay->drawOverlay(gameScreen);
		gameScreen.display();
	}
}


// initializeGameScreen function
void Game::initializeGameScreen()
{
	// Creates a new mothership
	if (mothership != nullptr) {
		delete mothership;
		mothership = nullptr;
	}
	mothership = new SpaceObject{ SHIP_GONE, 5, { SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 }, {0, 0}, 0, 0 };

	// Creates 5 new starting asteroids
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr) {
			delete asteroids[i];
			asteroids[i] = nullptr;
		}
	}
	for (int i = 0; i < MAX_ASTEROIDS / 4; i++) {
		asteroids[i] = new SpaceObject{ ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 0, 0 };
	}

	// Deletes any leftover photons, if any
	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (photons[i] != nullptr) {
			delete photons[i];
			photons[i] = nullptr;
		}
	}

	// Sets game in progress to true
	gameOverlay->changeInProgress(true);
	gameOverlay->changeLifeTotal(3);
	gameOverlay->changeFirstLifeLost(false);
}

// processGameScreen function
void Game::processGameScreen()
{
	// Initializes the game screen
	gameOverlay->changeOverlay(INCOMING_SHIP);
	if (gameOverlay->getGameInProgress() == false)
		initializeGameScreen();

	// While the game screen is open
	while (gameScreen.isOpen() && screenState == GAME_SCREEN)
	{
		// Change overlay if the ship is respawning or not
		if (mothership->getType() == SHIP)
			gameOverlay->changeOverlay(GAME_OVERLAY);
		else if (mothership->getType() == SHIP_GONE)
			gameOverlay->changeOverlay(INCOMING_SHIP);

		// For the user input events that happen on the game screen
		sf::Event event;
		while (gameScreen.isOpen() && gameScreen.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				screenState = EXIT_SCREEN;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M && gameOverlay->pauseScreenIsOpen() == false)
				this->screenState = TITLE_SCREEN;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && gameOverlay->pauseScreenIsOpen() == false)
				initializeGameScreen();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && gameOverlay->pauseScreenIsOpen() == false && (mothership->getType() == SHIP || mothership->getType() == SHIP_THRUST)) {
				for (int i = 0; i < MAX_PHOTONS; i++) {
					if (photons[i] == nullptr) {
						photons[i] = new SpaceObject{ PHOTON_TORPEDO, 2, mothership->getLocation(), mothership->getVelocity(), mothership->getAngle(), 0 };
						photons[i]->applyThrust(5);
						break;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && (mothership->getType() == SHIP || mothership->getType() == SHIP_THRUST)) {
				if (gameOverlay->pauseScreenIsOpen())
					closePauseScreen();
				else
					openPauseScreen();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gameOverlay->pauseScreenIsOpen() == false)
			mothership->changeAngle(-5);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gameOverlay->pauseScreenIsOpen() == false)
			mothership->changeAngle(5);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && gameOverlay->pauseScreenIsOpen() == false && (mothership->getType() == SHIP || mothership->getType() == SHIP_THRUST)) {
			mothership->changeObjType(SHIP_THRUST);
			mothership->applyThrust(0.05);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false && mothership->getType() == SHIP_THRUST && gameOverlay->pauseScreenIsOpen() == false)
			mothership->changeObjType(SHIP);

		// For the respawn of the mothership after it's gone
		if (mothership->getType() == SHIP_GONE)
			respawnShip();

		// Rotates the asteroids
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr)
				asteroids[i]->changeAngle(1);
		}

		// Updates game objects
		mothership->updatePosition();

		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr)
				asteroids[i]->updatePosition();
		}

		for (int i = 0; i < MAX_PHOTONS; i++) {
			if (photons[i] != nullptr) {
				photons[i]->updatePosition();
				if (photons[i]->getTimesDrawn() > PHOTON_LIFESPAN) {
					delete photons[i];
					photons[i] = nullptr;
				}
			}
		}

		// For the collision of the ship or a photon with an asteroid
		shipHitAsteroid();
		photonHitAsteroid();

		// Drawing the new frame
		gameScreen.clear();
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr) {
				asteroids[i]->draw(gameScreen);
			}
		}
		for (int i = 0; i < MAX_PHOTONS; i++) {
			if (photons[i] != nullptr) {
				photons[i]->draw(gameScreen);
				if (gameOverlay->pauseScreenIsOpen() == false)
					photons[i]->incrementTimesDrawn();
			}
		}
		mothership->draw(gameScreen);
		gameOverlay->drawOverlay(gameScreen);
		gameScreen.display();

		// For if the ship is exploding
		if (mothership->getType() == SHIP_EXPLODING) {
			mothership->setRadius(mothership->getRadius() + .2);
			mothership->setLocation(mothership->getLocation().x - .2, mothership->getLocation().y - .2);

			// For when the ship is done exploding
			if (mothership->getRadius() > 12) {
				mothership->changeObjType(SHIP_GONE);
				mothership->setLocation(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
				mothership->setRadius(5);

				// Tests if the game is over via no lives left
				if (gameOverlay->getLivesLeft() == 0)
					this->screenState = GAME_OVER;
				else
					this->screenState = LIVES_SCREEN;
			}
		}

		// Tests if the game is over via no asteroids remaining
		if (testIfGameOver()) {
			this->screenState = GAME_OVER;
		}
	}
}

// initializeOverScreen function
void Game::initializeOverScreen()
{
	// Deletes any leftover photons, if any
	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (photons[i] != nullptr) {
			delete photons[i];
			photons[i] = nullptr;
		}
	}

	// If the player wins, only create a new ship for the drawing animation
	if (gameOverlay->getLivesLeft() >= 0 && (mothership->getType() == SHIP || mothership->getType() == SHIP_THRUST)) {
		gameOverlay->changeOverlay(PLAYER_WINS);
		if (mothership != nullptr) {
			delete mothership;
			mothership = nullptr;
		}
		mothership = new SpaceObject{ SHIP, 5, getRandomLocation(), getRandomVelocity(), 0, 0 };

	}
	// If the player loses, only create new asteroids for the drawing animation
	else if (gameOverlay->getLivesLeft() == 0 && mothership->getType() == SHIP_GONE) {
		gameOverlay->changeOverlay(PLAYER_LOSES);

		if (mothership != nullptr) {
			delete mothership;
			mothership = nullptr;
		}

		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr) {
				delete asteroids[i];
				asteroids[i] = nullptr;
			}
		}
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (i >= 0 && i < 5)
				asteroids[i] = new SpaceObject{ ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 0, 0 };
			else if (i >= 5 && i < 10)
				asteroids[i] = new SpaceObject{ ASTEROID, 10, getRandomLocation(), getRandomVelocity(), 0, 0 };
			else if (i >= 10 && i < 15)
				asteroids[i] = new SpaceObject{ ASTEROID, 5, getRandomLocation(), getRandomVelocity(), 0, 0 };
		}
	}
}

// processOverScreen function
void Game::processOverScreen()
{
	// Initializes the game over screen and resets some game overlay values
	initializeOverScreen();

	// While the game over screen is open
	while (gameScreen.isOpen() && screenState == GAME_OVER) {
		// For the user input events that happen on the game over screen
		sf::Event event;
		while (gameScreen.isOpen() && gameScreen.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				screenState = EXIT_SCREEN;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M && gameOverlay->pauseScreenIsOpen() == false)
				this->screenState = TITLE_SCREEN;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				if (gameOverlay->pauseScreenIsOpen())
					closePauseScreen();
				else
					openPauseScreen();
			}
		}

		// Drawing the new frame
		gameScreen.clear();
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i] != nullptr) {
				asteroids[i]->changeAngle(1);
				asteroids[i]->updatePosition();
				asteroids[i]->draw(gameScreen);
			}
		}
		if (mothership != nullptr) {
			mothership->changeAngle(3);
			mothership->updatePosition();
			mothership->draw(gameScreen);
		}
		gameOverlay->drawOverlay(gameScreen);
		gameScreen.display();
	}
}

// initializeLifeScreen function
void Game::initializeLifeScreen()
{
	// Variables to initialize the lifeShips with
	Point noVelocity = { 0,0 };
	Point locationOne = { 100, 200 };
	Point locationTwo = { 200, 200 };
	Point locationThree = { 300, 200 };

	// Creates 3 lifeships to represent 3 lives left
	for (int i = 0; i < MAX_LIVES; i++) {
		delete lifeShips[i];
		lifeShips[i] = nullptr;
	}
	lifeShips[0] = new SpaceObject{ SHIP, 15, locationOne, noVelocity, 0, 0 };
	lifeShips[1] = new SpaceObject{ SHIP, 15, locationTwo, noVelocity, 0, 0 };
	lifeShips[2] = new SpaceObject{ SHIP, 15, locationThree, noVelocity, 0, 0 };
}

// processLivesScreen function
void Game::processLivesScreen()
{
	// Initializes the lives left screen
	gameOverlay->changeOverlay(LIVES_LEFT);

	// While the lives left screen is open
	while (gameScreen.isOpen() && screenState == LIVES_SCREEN) {
		// For the user input events that happen on the lives left screen
		sf::Event event;
		while (gameScreen.isOpen() && gameScreen.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				screenState = EXIT_SCREEN;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				if (gameOverlay->pauseScreenIsOpen())
					closePauseScreen();
				else
					openPauseScreen();
			}
		}
		// If this is the first life lost this game, initialize the life screen overlay
		if (gameOverlay->isFirstLifeLost() == false) {
			initializeLifeScreen();
			gameOverlay->changeFirstLifeLost(true);
		}

		// Decrements the life total
		gameOverlay->changeLifeTotal(gameOverlay->getLivesLeft() - 1);
		gameOverlay->changeFirstLifeLost(true);

		// Draws the lives left ships onto the game screen
		while (lifeShips[gameOverlay->getLivesLeft()]->getTimesDrawn() < 50 && screenState == LIVES_SCREEN) {
			while (gameScreen.isOpen() && gameScreen.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					screenState = EXIT_SCREEN;
			}
			gameScreen.clear();
			for (int i = 0; i < MAX_LIVES; i++) {
				lifeShips[i]->draw(gameScreen);
				lifeShips[i]->incrementTimesDrawn();
			}
			gameOverlay->drawOverlay(gameScreen);
			gameScreen.display();
		}

		// For the loss of a life (explode a lifeShip)
		lifeShips[gameOverlay->getLivesLeft()]->explode();

		// Draws the exploding life ship and other life ships
		while (lifeShips[gameOverlay->getLivesLeft()]->getTimesDrawn() >= 50 && lifeShips[gameOverlay->getLivesLeft()]->getTimesDrawn() < 250 && screenState == LIVES_SCREEN) {
			while (gameScreen.isOpen() && gameScreen.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					screenState = EXIT_SCREEN;
			}
			gameScreen.clear();
			for (int i = 0; i < MAX_LIVES; i++) {
				lifeShips[i]->draw(gameScreen);
				lifeShips[i]->incrementTimesDrawn();
			}
			gameOverlay->drawOverlay(gameScreen);
			gameScreen.display();

			// For when the lifeShip is exploding
			if (lifeShips[gameOverlay->getLivesLeft()]->getType() == SHIP_EXPLODING) {
				lifeShips[gameOverlay->getLivesLeft()]->setRadius(lifeShips[gameOverlay->getLivesLeft()]->getRadius() + .1);
				lifeShips[gameOverlay->getLivesLeft()]->setLocation(lifeShips[gameOverlay->getLivesLeft()]->getLocation().x - .1, lifeShips[gameOverlay->getLivesLeft()]->getLocation().y - .1);

				// For when the lifeShip is done exploding
				if (lifeShips[gameOverlay->getLivesLeft()]->getRadius() > 12) {
					lifeShips[gameOverlay->getLivesLeft()]->changeObjType(SHIP_GONE);
					lifeShips[gameOverlay->getLivesLeft()]->setLocation(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
					lifeShips[gameOverlay->getLivesLeft()]->setRadius(5);
				}
			}
		}

		// Resets the times drawn for the lifeships
		for (int i = 0; i < MAX_LIVES; i++) {
			lifeShips[i]->setTimesDrawn(0);
		}

		// Deletes any remaining photons from when the ship exploded
		for (int i = 0; i < MAX_PHOTONS; i++) {
			if (photons[i] != nullptr) {
				delete photons[i];
				photons[i] = nullptr;
			}
		}
		
		if (screenState == LIVES_SCREEN) {
			this->screenState = GAME_SCREEN;
		}
	}
}

// openPauseScreen function
void Game::openPauseScreen()
{
	// changes the pauseScreenIsOpen variable to true
	gameOverlay->changePauseScreenOpen(true);

	// Copying over the current game screen objects
	if (mothership != nullptr) {
		copyMothership = new SpaceObject;
		copyMothership->setVelocity(mothership->getVelocity().x, mothership->getVelocity().y);
		mothership->setVelocity(0, 0);
	}
	for (int i = 0; i < MAX_LIVES; i++) {
		if (lifeShips[i] != nullptr) {
			copyLifeships[i] = new SpaceObject;
			copyLifeships[i]->setVelocity(lifeShips[i]->getVelocity().x, lifeShips[i]->getVelocity().y);
			lifeShips[i]->setVelocity(0, 0);
		}
	}
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr) {
			copyAsteroids[i] = new SpaceObject;
			copyAsteroids[i]->setVelocity(asteroids[i]->getVelocity().x, asteroids[i]->getVelocity().y);
			asteroids[i]->setVelocity(0, 0);
		}
	}
	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (photons[i] != nullptr) {
			copyPhotons[i] = new SpaceObject;
			copyPhotons[i]->setVelocity(photons[i]->getVelocity().x, photons[i]->getVelocity().y);
			photons[i]->setVelocity(0, 0);
		}
	}
}

// closePauseScreen function
void Game::closePauseScreen()
{
	// changes the pauseScreenIsOpen variable to false
	gameOverlay->changePauseScreenOpen(false);

	// Resetting the space objects to their original velocities
	if (mothership != nullptr)
		mothership->setVelocity(copyMothership->getVelocity().x, copyMothership->getVelocity().y);
	for (int i = 0; i < MAX_LIVES; i++) {
		if (lifeShips[i] != nullptr)
			lifeShips[i]->setVelocity(copyLifeships[i]->getVelocity().x, copyLifeships[i]->getVelocity().y);
	}
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr)
			asteroids[i]->setVelocity(copyAsteroids[i]->getVelocity().x, copyAsteroids[i]->getVelocity().y);
	}
	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (photons[i] != nullptr)
			photons[i]->setVelocity(copyPhotons[i]->getVelocity().x, copyPhotons[i]->getVelocity().y);
	}

	// Deleting the copies of the space objects
	if (copyMothership != nullptr) {
		delete copyMothership;
		copyMothership = nullptr;
	}
	for (int i = 0; i < MAX_LIVES; i++) {
		if (copyLifeships[i] != nullptr) {
			delete copyLifeships[i];
			copyLifeships[i] = nullptr;
		}
	}
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (copyAsteroids[i] != nullptr) {
			delete copyAsteroids[i];
			copyAsteroids[i] = nullptr;
		}
	}
	for (int i = 0; i < MAX_PHOTONS; i++) {
		if (copyPhotons[i] != nullptr) {
			delete copyPhotons[i];
			copyPhotons[i] = nullptr;
		}
	}
}

// respawnShip function
void Game::respawnShip()
{
	// Counts the asteroids and sees if they intersect with the ship
	int asteroidCount = 0;
	int noIntersectCount = 0;

	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr) {
			asteroidCount++;
			if (objectsIntersect(mothership, asteroids[i]) == false) {
				noIntersectCount++;
			}
		}
	}

	// Respawns the ship if they don't intersect
	if (noIntersectCount == asteroidCount) {
		asteroidCount = 0;
		noIntersectCount = 0;
		mothership->changeObjType(SHIP);
	}
	else {
		asteroidCount = 0;
		noIntersectCount = 0;
	}
}

// shipHitAsteroid function
void Game::shipHitAsteroid()
{
	// For the collision of the mothership with asteroids
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr) {
			if (objectsIntersect(mothership, asteroids[i]) && mothership->getType() == SHIP ||
				objectsIntersect(mothership, asteroids[i]) && mothership->getType() == SHIP_THRUST) {
				mothership->explode();
			}
		}
	}
}

// photonHitAsteroid function
void Game::photonHitAsteroid()
{
	// For the collision of a photon torpedo with an asteroid
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		for (int j = 0; j < MAX_PHOTONS; j++) {
			if (asteroids[i] != nullptr && photons[j] != nullptr) {
				if (objectsIntersect(photons[j], asteroids[i])) {
					// Deletes the current photon torpedo
					delete photons[j];
					photons[j] = nullptr;

					// Create two new asteroids at half the size of the previous until it's 1/4 the original size
					if (asteroids[i]->getRadius() > compareAsteroid->getRadius() / 4) {
						for (int k = 0; k < MAX_ASTEROIDS; k++) {
							if (asteroids[k] == nullptr) {
								asteroids[k] = new SpaceObject{ ASTEROID, (asteroids[i]->getRadius() / 2), asteroids[i]->getLocation(), getRandomVelocity(), 0, 0 };
								break;
							}
						}
						for (int l = 0; l < MAX_ASTEROIDS; l++) {
							if (asteroids[l] == nullptr) {
								asteroids[l] = new SpaceObject{ ASTEROID, (asteroids[i]->getRadius() / 2), asteroids[i]->getLocation(), getRandomVelocity(), 0, 0 };
								break;
							}
						}
					}
					// Deletes the current asteroid
					delete asteroids[i];
					asteroids[i] = nullptr;
				}
			}
		}
	}
}

// getRandomLocation function
Point Game::getRandomLocation()
{
	Point randomLocation = { rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
	this->objRandomLocation = randomLocation;
	return objRandomLocation;
}

// getRandomVelocity function
Point Game::getRandomVelocity()
{
	Point randomVelocity = { rand() % 200 + 1, rand() % 200 + 1 };

	// If the random velocity is between 1 and 100, the velocity will be a positive value between 0 and 1
	// If the random velocity is between 101 and 200, the velocity will be a negative value between -1 and 0
	if (randomVelocity.x < 100)
		randomVelocity.x = randomVelocity.x / 100;
	else
		randomVelocity.x = ((randomVelocity.x - 100) * -1) / 100;

	if (randomVelocity.y < 100)
		randomVelocity.y = randomVelocity.y / 100;
	else
		randomVelocity.y = ((randomVelocity.y - 100) * -1) / 100;

	this->objRandomVelocity = randomVelocity;

	return objRandomVelocity;
}

// objectsIntersect function
bool Game::objectsIntersect(SpaceObject* object1, SpaceObject* object2)
{
	double distanceBetween = sqrt(pow(object2->getLocation().x - object1->getLocation().x, 2) + pow(object2->getLocation().y - object1->getLocation().y, 2));
	if (distanceBetween < 0)
		distanceBetween = distanceBetween * -1;

	if (object1->getType() == SHIP || object1->getType() == SHIP_THRUST || object1->getType() == PHOTON_TORPEDO) {
		if (distanceBetween <= (object1->getRadius() + object2->getRadius()) * 1.25) // I used a multiplier of 1.25 to make the collision appear more accurate for the visual aspect
			return true;
		else
			return false;
	}
	else if (object1->getType() == SHIP_GONE) {
		if (distanceBetween <= (object1->getRadius() + object2->getRadius()) * 3) // I used a multiplier of 3 to give the new ship enough room to spawn in
			return true;
		else
			return false;
	}
}

// testIfGameOver function
bool Game::testIfGameOver()
{
	int maxShipDraw = 0; // To count how many times the ship is drawn after last asteroid is gone
	int asteroidsRemaining = 0; // To count the remaining asteroids

	// To test how many asteroids are left
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		if (asteroids[i] != nullptr) {
			asteroidsRemaining += 1;
		}
	}

	// Depending on how many asteroids are left
	if (asteroidsRemaining > 0)
		return false;
	else if (asteroidsRemaining == 0) {
		maxShipDraw = mothership->getTimesDrawn() + 50;
		while (mothership->getTimesDrawn() < maxShipDraw) {
			mothership->updatePosition();
			gameScreen.clear();
			mothership->draw(gameScreen);
			mothership->incrementTimesDrawn();
			gameScreen.display();
		}
		return true;
	}
}