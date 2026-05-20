/* ===================================================================================================================
@Author:		Tyson Koopman-Baker
@Date:			5/16/2025
@File:			game.h
@Version:		2.0
@IDE:			Microsoft Visual Studios 2022 - Community
@Description:	This program is the header file for the Game class type, used to create and play the Octogons video game
=================================================================================================================== */

#ifndef GAME_H
#define GAME_H
#include "spaceObject.h"
#include "gameOverlay.h"
#include "constants.h"

enum GameState { TITLE_SCREEN, GAME_SCREEN, GAME_OVER, EXIT_SCREEN, LIVES_SCREEN };

class Game
{
public:
	/* Constructors */

	/*
	*	The default constructor
	*/
	Game();

	/*
	*	The default destructor
	*/
	~Game();

	/* Mutator functions */

	/*
	*	Plays the game
	*/
	void playGame();

	/*
	*	Initializes the objects for the title screen
	*/
	void initializeTitleScreen();

	/*
	*	Processes the title screen
	*/
	void processTitleScreen();

	/*
	*	Initializes the objects for the game screen
	*/
	void initializeGameScreen();

	/*
	*	Processes the main game screen
	*/
	void processGameScreen();

	/*
	*	Initializes the objects for the game over screen
	*/
	void initializeOverScreen();

	/*
	*	Processes the game over screen
	*/
	void processOverScreen();

	/*
	*	Initializes the objects for the lives left screen
	*/
	void initializeLifeScreen();

	/*
	*	Processes the lives left screen
	*/
	void processLivesScreen();

	/*
	*	Pauses the objects for the pause screen
	*/
	void openPauseScreen();

	/*
	*	Restatrs the objects for the pause screen
	*/
	void closePauseScreen();

	/*
	*	Respawns the main ship
	*/
	void respawnShip();

	/*
	*	Goes throught the ship explosion process if the ship collides with an asteroid
	*/
	void shipHitAsteroid();

	/*
	*	Goes through the asteroid explosion process if a photon torpedo collides with an asteroid
	*/
	void photonHitAsteroid();

	/* Accessor functions */

	/*
	*	Gets a random location using the rand functions
	*
	*	@return	Point randomLocation - The random location being created
	*/
	Point getRandomLocation();

	/*
	*	Gets a random velocity using the rand functions
	*
	*	@return	Point randomVelocity - The random velocity being created
	*/
	Point getRandomVelocity();

	/*
	*	Calculates if two space objects have collided with each other
	*
	*	@param	SpaceObject* object1 - The first space object to compare
	*	@param	SpaceObject* object2 - The second space object to compare
	*	@return	bool true - If the two space objects collide
	*	@return bool false - If the two space objects don't collide
	*/
	bool objectsIntersect(SpaceObject* object1, SpaceObject* object2);

	/*
	*	Tests if there are no asteroids left (the game is over)
	*
	*	@return bool true - If there are no more asteroids left
	*	@return bool false - If there are still asteroids left
	*/
	bool testIfGameOver();

private:
	sf::RenderWindow gameScreen; // For the rendering of the game screen
	GameState screenState; // For the type of game screen active
	SpaceObject* mothership; // For the mothership on the game screen
	SpaceObject* lifeShips[MAX_LIVES]; // For the life ships on the game screen
	SpaceObject* asteroids[MAX_ASTEROIDS]; // For the asteroids on the game screen
	SpaceObject* compareAsteroid; // An original asteroid to compare to
	SpaceObject* photons[MAX_PHOTONS]; // For the photon torpedos on the game screen
	Point objRandomLocation; // For the random locations of space objects
	Point objRandomVelocity; // For the random velocities of space objects
	GameOverlay* gameOverlay; // For the gamescreen overlays
	SpaceObject* copyMothership; // For the copy of the mothership used for game pausing
	SpaceObject* copyLifeships[MAX_LIVES]; // For the copy of the lifeShips used for game pausing
	SpaceObject* copyAsteroids[MAX_ASTEROIDS]; // For the copy of the asteroids used for game pausing
	SpaceObject* copyPhotons[MAX_PHOTONS]; // For the copy of the photons used for game pausing
};

#endif