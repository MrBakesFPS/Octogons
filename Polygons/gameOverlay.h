/* ===================================================================================================================
@Author:		Tyson Koopman-Baker
@Date:			5/16/2025
@File:			GameOverlay.h
@Version:		2.0
@IDE:			Microsoft Visual Studios 2022 - Community
@Description:	This program is the header file for the OverlayState class, used to display overlays for the Octogons
				game screen. This is the file that contains the life total values as I see those values as being
				moreso directly related to the overlay rather than the ship itself. ie: Ship explodes = Change in
				overlay = Decrement in life total.
=================================================================================================================== */
#ifndef OVERLAY_H
#define OVERLAY_H

// enumerator for the types of overlays
enum OverlayState { TITLE_OVERLAY, GAME_OVERLAY, INCOMING_SHIP, PLAYER_WINS, PLAYER_LOSES, LIVES_LEFT};

// GameOverlay class
class GameOverlay
{
public:
	/* Constructors */

	/*
	*	Initializes the default GameOverlay constuctor
	*/
	GameOverlay();

	/* Mutator functions */

	/*
	*	Changes the current overlay type to a new one
	* 
	*	@param OverlayState newOverlayType - The new overlay type to be set to
	*/
	void changeOverlay(OverlayState newOverlayType);

	/*
	*	Draws the game overlay to the given window
	* 
	*	@param sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawOverlay(sf::RenderWindow& win);

	/*
	*	Changes the curent life total to a new life total
	* 
	*	@paream int newLifeTotal - The new life total to be set to
	*/
	void changeLifeTotal(int newLifeTotal);

	/*
	*	Changes if the first life is lost during a game via the parameter
	* 
	*	@param bool isFirstLifeLost - true/false if the first life is lost yet
	*/
	void changeFirstLifeLost(bool isFirstLifeLost);

	/*
	*	Changes if the game is currently in progress or not
	*
	*	@param bool isInProgress - true/false if the game is in progress or not
	*/
	void changeInProgress(bool isInProgress);

	/*
	*	Changes if the pause screen is open or not
	* 
	*	@param bool isOpen - If the pause screen is open or not
	*/
	void changePauseScreenOpen(bool isOpen);

	/* Accessor functions */

	/*
	*	Gets the total number of lives left in the game
	* 
	*	@return int lives - The total number of lives left
	*/
	int getLivesLeft();

	/*
	*	Gets if the game is in progress or not
	* 
	*	@return bool true - If the game is still in progress
	*	@return bool false - If the game is not in progress
	*/
	bool getGameInProgress();

	/*
	*	Gets if the first life is lost yet durring the game
	* 
	*	@return bool true - If the first life has been lost
	*	@return bool false - If the first life has not been lost 
	*/
	bool isFirstLifeLost();

	/*
	*	Gets if the pause screen is open or not
	* 
	*	@return bool true - If the pause screen is open
	*	@return bool false - If the pause screen is closed
	*/
	bool pauseScreenIsOpen();
	
private:
	OverlayState overlayType; // For the current type of overlay to display
	int lives; // For the total lives left in the game
	bool firstLifeLost; // If the first life has been lost yet in the game
	bool gameInProgress; // If the game is in prrogress or not
	sf::Font gameFont; // For the font to be used for the overlay text
	bool pauseScreenOpen; // For if the pause screen is open or not

	/* Other private functiosn */

	/*
	*	Draws the title overlay on the given window 
	*
	*	@param	sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawTitleOverlay(sf::RenderWindow& win);

	/*
	*	Draws the game overlay on the given window
	*
	*	@param	sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawGameOverlay(sf::RenderWindow& win);

	/*
	*	Draws the incoming ship overlay on the given window
	*
	*	@param	sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawIncomingShip(sf::RenderWindow& win);

	/*
	*	Draws the player wins overlay on the given window
	*
	*	@param	sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawWinOverlay(sf::RenderWindow& win);

	/*
	*	Draws the player loses overlay on the given window
	*
	*	@param	sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawLoseOverlay(sf::RenderWindow& win);

	/*
	*	Draws the lives left overlay on the given window
	*
	*	@param	sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawLivesOverlay(sf::RenderWindow& win);

	/*
	*	Draws the pause screen overlay on the given window
	* 
	*	@param sf::RenderWindow& win - The window on which the overlay is being drawn on
	*/
	void drawPauseOverlay(sf::RenderWindow& win);

};

#endif